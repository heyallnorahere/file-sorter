#include "pch.h"
#include "../misc.h"
#include "internal.h"
#include <shobjidl.h>
#include <Shlwapi.h>
//begin stolen code: https://github.com/pauldotknopf/WindowsSDK7-Samples/blob/master/winui/shell/appplatform/commonfiledialog/CommonFileDialogApp.cpp (sorry)
class CDialogEventHandler : public IFileDialogEvents,
    public IFileDialogControlEvents
{
public:
    // IUnknown methods
    IFACEMETHODIMP QueryInterface(REFIID riid, void** ppv)
    {
        static const QITAB qit[] = {
            QITABENT(CDialogEventHandler, IFileDialogEvents),
            QITABENT(CDialogEventHandler, IFileDialogControlEvents),
            { 0 },
        };
        return QISearch(this, qit, riid, ppv);
    }

    IFACEMETHODIMP_(ULONG) AddRef()
    {
        return InterlockedIncrement(&_cRef);
    }

    IFACEMETHODIMP_(ULONG) Release()
    {
        long cRef = InterlockedDecrement(&_cRef);
        if (!cRef)
            delete this;
        return cRef;
    }

    // IFileDialogEvents methods
    IFACEMETHODIMP OnFileOk(IFileDialog*) { return S_OK; };
    IFACEMETHODIMP OnFolderChange(IFileDialog*) { return S_OK; };
    IFACEMETHODIMP OnFolderChanging(IFileDialog*, IShellItem*) { return S_OK; };
    IFACEMETHODIMP OnHelp(IFileDialog*) { return S_OK; };
    IFACEMETHODIMP OnSelectionChange(IFileDialog*) { return S_OK; };
    IFACEMETHODIMP OnShareViolation(IFileDialog*, IShellItem*, FDE_SHAREVIOLATION_RESPONSE*) { return S_OK; };
	IFACEMETHODIMP OnTypeChange(IFileDialog* pfd) { return S_OK; }
    IFACEMETHODIMP OnOverwrite(IFileDialog*, IShellItem*, FDE_OVERWRITE_RESPONSE*) { return S_OK; };

    // IFileDialogControlEvents methods
	IFACEMETHODIMP OnItemSelected(IFileDialogCustomize* pfdc, DWORD dwIDCtl, DWORD dwIDItem) { return S_OK; }
    IFACEMETHODIMP OnButtonClicked(IFileDialogCustomize*, DWORD) { return S_OK; };
    IFACEMETHODIMP OnCheckButtonToggled(IFileDialogCustomize*, DWORD, BOOL) { return S_OK; };
    IFACEMETHODIMP OnControlActivating(IFileDialogCustomize*, DWORD) { return S_OK; };

    CDialogEventHandler() : _cRef(1) { };
private:
    ~CDialogEventHandler() { };
    long _cRef;
};
// Instance creation helper
HRESULT CDialogEventHandler_CreateInstance(REFIID riid, void** ppv)
{
    *ppv = NULL;
    CDialogEventHandler* pDialogEventHandler = new (std::nothrow) CDialogEventHandler();
    HRESULT hr = pDialogEventHandler ? S_OK : E_OUTOFMEMORY;
    if (SUCCEEDED(hr))
    {
        hr = pDialogEventHandler->QueryInterface(riid, ppv);
        pDialogEventHandler->Release();
    }
    return hr;
}
//end stolen code
namespace file_sorter {
	namespace platform {
        std::string convert_from_unicode(const std::wstring& str) {
            std::string new_string;
            for (auto c : str) {
                new_string.push_back(c);
            }
            return new_string;
        }
#define call(x) assert(SUCCEEDED(x))
		std::string open_folder_dialog(window_t window) {
			IFileDialog* pfd = NULL;
			call(CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd)));
			IFileDialogEvents* pfde = NULL;
			call(CDialogEventHandler_CreateInstance(IID_PPV_ARGS(&pfde)));
            DWORD cookie;
            call(pfd->Advise(pfde, &cookie));
            DWORD flags;
            call(pfd->GetOptions(&flags));
            call(pfd->SetOptions(flags | FOS_PICKFOLDERS));
            if (SUCCEEDED(pfd->Show(NULL))) {
                IShellItem* item;
                call(pfd->GetResult(&item));
                wchar_t* filepath = NULL;
                call(item->GetDisplayName(SIGDN_FILESYSPATH, &filepath));
                std::string ascii_filepath = convert_from_unicode(filepath);
                return ascii_filepath;
            }
			return "";
		}
	}
}