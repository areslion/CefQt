#pragma once

#ifndef QCEFCLIENT_H
#define QCEFCLIENT_H

int QCefInit(int &argc, char ** argv);

void QCefQuit();

QString AppGetWorkingDirectory();

#endif // QCEFCLIENT_H