class RunBeforeMain
{
public:
    RunBeforeMain()
    {
        HMODULE hNtDll = (HMODULE)LoadLibrary(_T("ntdll.dll"));
        FARPROC lpNeeded = GetProcAddress(hNtDll,"NtWaitForMultipleObjects");
        DebugBreakPoint();
    }
};

RunBeforeMain go;

int CALLBACK WinMain(
  _In_ HINSTANCE hInstance,
  _In_ HINSTANCE hPrevInstance,
  _In_ LPSTR     lpCmdLine,
  _In_ int       nCmdShow
)
{
}
