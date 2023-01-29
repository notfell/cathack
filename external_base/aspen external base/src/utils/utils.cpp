#include "../all.h"

namespace utils
{
    int screenWidth = 0;
    int screenHeight = 0;

    void unHook()
    {
        ExitProcess(1);
    }

    void hideConsole()
    {
        ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
    }

    void showConsole()
    {
        ::ShowWindow(::GetConsoleWindow(), SW_SHOW);
    }

    bool isConsoleVisible()
    {
        return ::IsWindowVisible(::GetConsoleWindow()) != FALSE;
    }

    const std::wstring stringToWstring(const std::string& str, const std::locale& loc)
    {
        std::vector<wchar_t> buf(str.size());
        std::use_facet<std::ctype<wchar_t>>(loc).widen(str.data(), str.data() + str.size(), buf.data());

        return std::wstring(buf.data(), buf.size());
    }

    void exit()
    {
        for (unsigned int i = 0; i < 3; i++)
        {
            printf("\rcloses in %i s", i);
            Sleep(i * 1000);
        }
        ExitProcess(1);
    }

    const int ch_MAX = 26;
    std::string randomString(int ch)
    {
        char alpha[ch_MAX] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',
                              'h', 'i', 'j', 'k', 'l', 'm', 'n',
                              'o', 'p', 'q', 'r', 's', 't', 'u',
                              'v', 'w', 'x', 'y', 'z' };
        std::string result = "";
        for (int i = 0; i < ch; i++)
            result = result + alpha[rand() % ch_MAX];

        return result;
    }

    void init()
    {
        HWND console = GetConsoleWindow();
        RECT r;

        int lenght = rand() % 15 + 10;

        srand(time(NULL));
 
        SetConsoleTitleA(randomString(lenght).c_str());

        GetWindowRect(console, &r);
        MoveWindow(console, r.left, r.top, 700, 530, TRUE);
    }

    const std::string getModulePathA()
    {
        static CHAR buffer[MAX_PATH];

        GetModuleFileNameA(NULL, buffer, MAX_PATH);

        std::string modulePath(buffer);

        size_t lastIndex = modulePath.find_last_of("/\\");

        return modulePath.substr(0, lastIndex);
    }

    bool isFileExistA(const std::string& _path)
    {
        std::ifstream file(_path);

        return file.good();
    }

    const std::wstring getRegeditKeyStringValue(const TCHAR* _groupPath, const TCHAR* _keyName)
    {
        CRegKey regKey;

        TCHAR applicationPath[255] = L"";
        ULONG currentApplicationPathChars = _countof(applicationPath);

        regKey.Open(HKEY_LOCAL_MACHINE, _groupPath);
        regKey.QueryStringValue(_keyName, applicationPath, &currentApplicationPathChars);
        regKey.Close();

        return std::wstring(applicationPath);
    }

    float lerp(float _a, float _b, float _t)
    {
        return (1.0f - _t) * _a + _t * _b;
    }

    void isKeyJustPressed(DWORD _key, std::function<void()> _function)
    {
        static ULONGLONG previousTick[UCHAR_MAX] = { 0 };
        static int baw = 200;

        if (((GetTickCount64() - previousTick[_key]) > baw))
        {
            if (isKeyPressed(_key))
            {
                _function();

                previousTick[_key] = GetTickCount64();
            }
        }
    }

    const std::string roundFloat(float _float, int _decimals)
    {
        std::ostringstream floatWithPrecision;

        floatWithPrecision << std::fixed << std::setprecision(_decimals) << _float;

        return floatWithPrecision.str();
    }

    bool worldToScreen(vector3 pos, vector3& screen, viewMatrix matrix, int windowWidth, int windowHeight)
    {
        //Matrix-vector Product, multiplying world(eye) coordinates by projection matrix = clipCoords
        quaternion clipCoords;
        clipCoords.x = pos.x * matrix.matrix[0] + pos.y * matrix.matrix[4] + pos.z * matrix.matrix[8] + matrix.matrix[12];
        clipCoords.y = pos.x * matrix.matrix[1] + pos.y * matrix.matrix[5] + pos.z * matrix.matrix[9] + matrix.matrix[13];
        clipCoords.z = pos.x * matrix.matrix[2] + pos.y * matrix.matrix[6] + pos.z * matrix.matrix[10] + matrix.matrix[14];
        clipCoords.w = pos.x * matrix.matrix[3] + pos.y * matrix.matrix[7] + pos.z * matrix.matrix[11] + matrix.matrix[15];

        if (clipCoords.w < 0.1f)
            return false;

        //perspective division, dividing by clip.W = Normalized Device Coordinates
        vector3 NDC;
        NDC.x = clipCoords.x / clipCoords.w;
        NDC.y = clipCoords.y / clipCoords.w;
        NDC.z = clipCoords.z / clipCoords.w;

        //Transform to window coordinates
        screen.x = (windowWidth / 2 * NDC.x) + (NDC.x + windowWidth / 2);
        screen.y = -(windowHeight / 2 * NDC.y) + (NDC.y + windowHeight / 2);

        //printf("s.x -> %f \n", screen.x);
        //printf("s.y -> %f \n", screen.y);

        return true;
    }

    float getDistance3D(vector3 m_pos, vector3 en_pos)
    {
        return (float)(sqrt(((en_pos.x - m_pos.x) * (en_pos.x - m_pos.x)) + ((en_pos.y - m_pos.y) * (en_pos.y - m_pos.y)) + ((en_pos.z - m_pos.z) * (en_pos.z - m_pos.z))));
    }

    float getDistance2D(vector3 m_pos, vector3 en_pos)
    {
        return { (float)(sqrt(
        ((en_pos.x - m_pos.x) * (en_pos.x - m_pos.x))
        + ((en_pos.z - m_pos.z) * (en_pos.z - m_pos.z))
        )) };
    }

    vector3 calculateAngles(vector3 _from, vector3 _to)
    {
        vector3 newAngles;
        vector3 ipotenuse = _to - _from;

        float Side = _to.z - _from.z;
        float Ipotenuse = ipotenuse.length();
        float pitch = asin(Side / Ipotenuse) * 180 / (float)PI;

        newAngles.y = pitch;

        float yaw = -atan2f(_to.x - _from.x, _to.y - _from.y) / (float)PI * 180 + 180;

        newAngles.x = yaw;
        newAngles.z = 0;

        return newAngles;
    }

    float radianToDegree(float radian)
    {
        return radian * (180 / PI);
    }

    float degreeToRadian(float degree)
    {
        return degree * (PI / 180);

    }

    vector3 radianToDegree(vector3 radians)
    {
        vector3 degrees;
        degrees.x = radians.x * (180 / PI);
        degrees.y = radians.y * (180 / PI);
        degrees.z = radians.z * (180 / PI);
        return degrees;
    }

    vector3 degreeToRadian(vector3 degrees)
    {
        vector3 radians;
        radians.x = degrees.x * (PI / 180);
        radians.y = degrees.y * (PI / 180);
        radians.z = degrees.z * (PI / 180);
        return radians;
    }

    vector3 lerp(vector3 _a, vector3 _b, float _t)
    {
        vector3 result;

        result.x = lerp(_a.x, _b.x, _t);
        result.y = lerp(_a.y, _b.y, _t);
        result.z = lerp(_a.z, _b.z, _t);
        
        return result;
    }
}