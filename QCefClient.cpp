#include "stdafx.h"

#include "QCefClient.h"
#include "QCefClientHandler.h"
#include "QCefClientApp.h"

namespace
{
	void QCefInitSettings(CefSettings & settings)
	{
		settings.multi_threaded_message_loop = true;
		settings.single_process = false;

		settings.ignore_certificate_errors = true;
		settings.command_line_args_disabled = true;
		CefString(&settings.locale).FromASCII("zh-CN");

		std::string cache_path = AppGetWorkingDirectory().toStdString() + "/.cache";
		CefString(&settings.cache_path) = CefString(cache_path);

		settings.log_severity = LOGSEVERITY_DISABLE;

		settings.no_sandbox = true;
	}
}

CefRefPtr<QCefClientHandler> g_handler;

int QCefInit(int& argc, char** argv)
{
	HINSTANCE hInstance = static_cast<HINSTANCE>(GetModuleHandle(nullptr));

	CefMainArgs mainArgs(hInstance);
	CefRefPtr<QCefClientApp> app(new QCefClientApp);

	int exit_code = CefExecuteProcess(mainArgs, app.get(), nullptr);
	if (exit_code >= 0) {
		return exit_code;
	}

	CefSettings settings;
	QCefInitSettings(settings);

	CefInitialize(mainArgs, settings, app, nullptr);

	g_handler = new QCefClientHandler();

	return -1;
}

void QCefQuit()
{
	//CefQuitMessageLoop();
	//g_handler->CloseAllBrowsers(true);
	//g_handler->DoClose(g_handler->GetBrowser());
	
	CefShutdown();
}

QString AppGetWorkingDirectory()
{
	return qApp->applicationDirPath();
}