/*
 * 	This file is part of Nanomite.
 *
 *    Nanomite is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    Nanomite is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with Nanomite.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "qtDLGHandleView.h"
#include "qtDLGNanomite.h"

#include "clsAPIImport.h"
#include "clsMemManager.h"
#include "clsClipboardHelper.h"
#include "NativeHeaders.h"

qtDLGHandleView::qtDLGHandleView(QWidget *parent, Qt::WFlags flags,qint32 processID)
	: QWidget(parent, flags),
	m_processID(processID),
	m_processCountEntry(0)
{
	setupUi(this);
	this->setAttribute(Qt::WA_DeleteOnClose,true);
	this->setLayout(verticalLayout);

	connect(tblHandleView,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(OnCustomContextMenuRequested(QPoint)));
	connect(new QShortcut(QKeySequence("F5"),this),SIGNAL(activated()),this,SLOT(OnDisplayHandles()));
	connect(new QShortcut(Qt::Key_Escape,this),SIGNAL(activated()),this,SLOT(close()));
	
	// Init List
	tblHandleView->horizontalHeader()->resizeSection(0,75);
	tblHandleView->horizontalHeader()->resizeSection(1,135);
	tblHandleView->horizontalHeader()->resizeSection(2,135);
	tblHandleView->horizontalHeader()->setFixedHeight(21);

	qtDLGNanomite *myMainWindow = qtDLGNanomite::GetInstance();

	m_processCountEnd = myMainWindow->coreDebugger->PIDs.size();
	for(int i = 0; i < myMainWindow->coreDebugger->PIDs.size(); i++)
	{
		if(myMainWindow->coreDebugger->PIDs[i].dwPID == m_processID)
		{
			m_processCountEntry = i;
			m_processCountEnd = i + 1;
			break;
		}
	}

	OnDisplayHandles();
}

qtDLGHandleView::~qtDLGHandleView()
{

}

void qtDLGHandleView::InsertDataIntoTable(DWORD dwPID,DWORD dwHandle,PTCHAR ptType,PTCHAR ptName)
{
	tblHandleView->insertRow(tblHandleView->rowCount());

	tblHandleView->setItem(tblHandleView->rowCount() - 1,0,
		new QTableWidgetItem(QString().sprintf("%08X",dwPID)));

	tblHandleView->setItem(tblHandleView->rowCount() - 1,1,
		new QTableWidgetItem(QString().sprintf("%08X",dwHandle)));

	tblHandleView->setItem(tblHandleView->rowCount() - 1,2,
		new QTableWidgetItem(QString::fromStdWString(ptType)));

	tblHandleView->setItem(tblHandleView->rowCount() - 1,3,
		new QTableWidgetItem(QString::fromStdWString(ptName)));
}

void qtDLGHandleView::OnDisplayHandles()
{
	qtDLGNanomite *myMainWindow = qtDLGNanomite::GetInstance();

	tblHandleView->setRowCount(0);
	for(int i = m_processCountEntry; i < m_processCountEnd;i++)
	{
		NTSTATUS status;
		ULONG handleInfoSize = 0x10000;
		DWORD dwPID = myMainWindow->coreDebugger->PIDs[i].dwPID;
		HANDLE hProc = myMainWindow->coreDebugger->PIDs[i].hProc;

		PSYSTEM_HANDLE_INFORMATION handleInfo = (PSYSTEM_HANDLE_INFORMATION)malloc(handleInfoSize);

		while ((status = clsAPIImport::pNtQuerySystemInformation(SystemHandleInformation,handleInfo,handleInfoSize,NULL)) == STATUS_INFO_LENGTH_MISMATCH)
			handleInfo = (PSYSTEM_HANDLE_INFORMATION)realloc(handleInfo, handleInfoSize *= 2);

		if (!NT_SUCCESS(status))
		{
			MessageBox(NULL,L"NtQuerySystemInformation failed!",L"Nanomite",MB_OK);
			close();
		}

		for (DWORD iCount = 0; iCount < handleInfo->HandleCount; iCount++)
		{
			SYSTEM_HANDLE handle = handleInfo->Handles[iCount];
			HANDLE dupHandle = NULL;
			POBJECT_TYPE_INFORMATION objectTypeInfo;
			PVOID objectNameInfo;
			UNICODE_STRING objectName;
			ULONG returnLength;

			if (handle.ProcessId != dwPID)
				continue;

			if (!NT_SUCCESS(clsAPIImport::pNtDuplicateObject(hProc,(HANDLE)handle.Handle,GetCurrentProcess(),&dupHandle,0,0,0)))
				continue;

			objectTypeInfo = (POBJECT_TYPE_INFORMATION)malloc(0x1000);
			if (!NT_SUCCESS(clsAPIImport::pNtQueryObject(dupHandle,ObjectTypeInformation,objectTypeInfo,0x1000,NULL)))
			{
				CloseHandle(dupHandle);
				free(objectTypeInfo);
				continue;
			}
			
			if (handle.GrantedAccess == 0x0012019f)
			{
				InsertDataIntoTable(dwPID,(DWORD)handle.Handle,objectTypeInfo->Name.Buffer,L"Did not get name");
				free(objectTypeInfo);
				CloseHandle(dupHandle);
				continue;
			}

			objectNameInfo = malloc(0x1000);
			if (!NT_SUCCESS(clsAPIImport::pNtQueryObject(dupHandle,ObjectNameInformation,objectNameInfo,0x1000,&returnLength)))
			{
				objectNameInfo = realloc(objectNameInfo, returnLength);
				if (!NT_SUCCESS(clsAPIImport::pNtQueryObject(dupHandle,ObjectNameInformation,objectNameInfo,returnLength,NULL)))
				{
					InsertDataIntoTable(dwPID,(DWORD)handle.Handle,objectTypeInfo->Name.Buffer,L"Could not get name");
					free(objectTypeInfo);
					free(objectNameInfo);
					CloseHandle(dupHandle);
					continue;
				}
			}

			objectName = *(PUNICODE_STRING)objectNameInfo;

			if (objectName.Length)
				InsertDataIntoTable(dwPID,(DWORD)handle.Handle,objectTypeInfo->Name.Buffer,objectName.Buffer);
			else
				InsertDataIntoTable(dwPID,(DWORD)handle.Handle,objectTypeInfo->Name.Buffer,L"unnamed");

			free(objectTypeInfo);
			free(objectNameInfo);
			CloseHandle(dupHandle);
		}
		free(handleInfo);
	}
}

void qtDLGHandleView::OnCustomContextMenuRequested(QPoint qPoint)
{
	QMenu menu;

	m_selectedRow = tblHandleView->indexAt(qPoint).row();
	if(m_selectedRow < 0) return;

	QMenu *submenu = menu.addMenu("Copy to Clipboard");
	submenu->addAction(new QAction("Line",this));
	submenu->addAction(new QAction("Handle",this));
	submenu->addAction(new QAction("Type",this));
	submenu->addAction(new QAction("Name",this));

	menu.addMenu(submenu);
	connect(&menu,SIGNAL(triggered(QAction*)),this,SLOT(MenuCallback(QAction*)));

	menu.exec(QCursor::pos());
}

void qtDLGHandleView::MenuCallback(QAction* pAction)
{
	if(QString().compare(pAction->text(),"Line") == 0)
	{
		QClipboard* clipboard = QApplication::clipboard();
		clipboard->setText(clsClipboardHelper::getTableToClipboard(tblHandleView, -1));
	}
	else if(QString().compare(pAction->text(),"Handle") == 0)
	{
		QClipboard* clipboard = QApplication::clipboard();
		clipboard->setText(clsClipboardHelper::getTableToClipboard(tblHandleView, 1));
	}
	else if(QString().compare(pAction->text(),"Type") == 0)
	{
		QClipboard* clipboard = QApplication::clipboard();
		clipboard->setText(clsClipboardHelper::getTableToClipboard(tblHandleView, 2));
	}
	else if(QString().compare(pAction->text(),"Name") == 0)
	{
		QClipboard* clipboard = QApplication::clipboard();
		clipboard->setText(clsClipboardHelper::getTableToClipboard(tblHandleView, 3));
	}
}