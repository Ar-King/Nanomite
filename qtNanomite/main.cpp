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
#include "qtDLGNanomite.h"

#include "clsCrashHandler.h"
#include "clsMemManager.h"

#include <WinBase.h>

BOOL IsUserAdmin()
{
    BOOL _isUserAdmin = false;

    SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
    PSID AdministratorsGroup;

    if (AllocateAndInitializeSid(&NtAuthority,2,SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS,0,0,0,0,0,0,&AdministratorsGroup))
    {
        CheckTokenMembership( NULL, AdministratorsGroup, &_isUserAdmin);
        
        FreeSid(AdministratorsGroup);
    }    

    return _isUserAdmin;
}

bool EnableDebugFlag()
{
	TOKEN_PRIVILEGES tkpNewPriv;
	LUID luid;
	HANDLE hToken = NULL;

	if(!OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES,&hToken))
		return false;

	if (!LookupPrivilegeValue(NULL,SE_DEBUG_NAME,&luid))
	{
		CloseHandle(hToken);
		return false;
	}

	tkpNewPriv.PrivilegeCount = 1;
	tkpNewPriv.Privileges[0].Luid = luid;
	tkpNewPriv.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	if(!AdjustTokenPrivileges(hToken,0,&tkpNewPriv,0,0,0))
	{
		CloseHandle(hToken);
		return false;
	}
	
	CloseHandle(hToken);
	return true;
}

int main(int argc, char *argv[])
{
	clsMemManager clsMManage = clsMemManager();
	
	AddVectoredExceptionHandler(1,clsCrashHandler::ErrorReporter);

    if (!IsUserAdmin())
    {
        if(MessageBoxW(NULL,L"Nanomite was started without Admin rights!\r\nThis could cause problems with some features!\r\n\r\nDo you want to restart it now with Admin rights?",L"Nanomite", MB_YESNO) == IDYES)
		{
			TCHAR fileName[MAX_PATH];
			if(GetModuleFileNameW(NULL,fileName, MAX_PATH) > 0)
			{
				if((int)ShellExecute(NULL,L"runas", fileName, GetCommandLineW(), NULL, SW_SHOW) > 32)
				{
					TerminateProcess(GetCurrentProcess(),0);
				}
			}
		}
    }

	if(!EnableDebugFlag())
	{
		MessageBoxW(NULL,L"ERROR, Unable to enable Debug Privilege!\r\nThis could cause problems with some features",L"Nanomite",MB_OK);
	}

	QApplication a(argc, argv);
	qtDLGNanomite w;
	w.show();

#ifdef _DEBUG
	return a.exec(); 
#else
	// ugly workaround for cruntime crash caused by new override!
	TerminateProcess(GetCurrentProcess(),a.exec());
#endif
}
