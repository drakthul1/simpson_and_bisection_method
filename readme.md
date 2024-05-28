Hướng dẫn cài đặt và chạy cho window:
Khuyến cáo sử dụng text editor/IDE Visual Studio Code và tải xuống compiler với link sau https://github.com/mstorsjo/llvm-mingw/releases/download/20240518/llvm-mingw-20240518-msvcrt-i686.zip, sau khi tải xong, giải nén và add đường dẫn thư mục bin trong thư mục chính đã giải nén vào trong biến môi trường PATH của user và restart lại vscode, sau đó mở terminal trong vscode vã gõ clang--version để kiểm tra xem vscode đã nhận compiler chưa.Nếu thông báo:
clang version 18.1.6 (https://github.com/llvm/llvm-project.git 1118c2e05e67a36ed8ca250524525cdb66a55256)
Target: i686-w64-windows-gnu
Thread model: posix
InstalledDir: D:/Downloads/llvm-mingw-20240518-msvcrt-i686/llvm-mingw-20240518-msvcrt-i686/bin
Thì đã thành công, và có thể thực hiện các bước dưới đây:
Lệnh Build và Run của từng phương pháp theo file:
- Build phương pháp chia đôi:  clang++ bisection.cpp -o bisection
- Run phương pháp chia đôi: .\bisection.exe
- Build phương pháp simson: clang++ simpson.cpp -o simpson
- Run phương pháp simpson: .\simpson.exe
Lưu ý trước khi chạy :
- Sửa lại đường dẫn thư viện exprtk.hpp, sửa lại include theo đúng đường dẫn tuyệt đối trên máy.
- Fix lỗi ký tự Tiếng Việt hiển thị trên terminal: gõ lệnh chcp 65001 vào trong cmd,powershell,... sau mỗi lần mở lại cmd,powershell hoặc add setting sau vào settings.json(có thể tìm bằng cách nhấn tổ hợp phím Ctrl + P và gõ setting) và restart vscode:
"terminal.integrated.profiles.windows": {
        "PowerShell": {
            "source": "PowerShell",
            "icon": "terminal-powershell",
            "args": [
                "-NoExit",
                "/c",
                "chcp.com 65001"
            ]
        },
        "Command Prompt": {
            "path": [
                "${env:windir}\\Sysnative\\cmd.exe",
                "${env:windir}\\System32\\cmd.exe"
            ],
            "args": [
                "/K",
                "chcp 65001"
            ],
            "icon": "terminal-cmd"
        },
    },

Chưa có hướng dẫn cho macOS và linux based system