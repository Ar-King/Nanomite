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
#ifndef CLSAPPSETTINGS_H
#define CLSAPPSETTINGS_H

#include <QObject>
#include <qmainwindow.h>
#include <qmutex.h>
#include <qsettings.h>

#include "../clsDebugger/clsDebugger.h"
#include "clsSymbolAndSyntax.h"

class clsAppSettings : public QObject
{
	Q_OBJECT

public:
	void SaveWindowState(QMainWindow* window);
	bool RestoreWindowState(QMainWindow* window);
	void ResetWindowState();

	void SaveDebuggerSettings();
	void SaveDisassemblerColor();
	void SaveDefaultJITDebugger(QString savedJIT, QString savedJITWOW64);
	void LoadDebuggerSettings();
	void LoadDisassemblerColor();
	void LoadDefaultJITDebugger(QString& savedJIT, QString& savedJITWOW64);
	void WriteDefaultSettings();
	void CheckIfFirstRun();
	void SaveRecentDebuggedFiles(QStringList recentDebuggedFiles);
	void LoadRecentDebuggedFiles(QStringList &recentDebuggedFiles);

	static clsAppSettings* SharedInstance();

	clsAppSettings();
	~clsAppSettings();

protected:
	//QSettings *appSettings;
	QSettings *userSettings;

private:
	static clsAppSettings *instance;
	QMutex *readWriteMutex;

	clsDebugger *m_pDebugger;
	disasColors	*m_pColors;
};

#endif // CLSAPPSETTINGS_H
