#pragma once
#include <string>
#include <vector>

namespace HardwareMonitor
{
    struct ItemInfo
    {
        std::wstring identifyer;    //Ψһ��ʶ��
        int decimal_places;         //С��λ��

        ItemInfo()
            : decimal_places(2)
        {}

        ItemInfo(const std::wstring& _identifyer)
            : identifyer(_identifyer), decimal_places(2)
        {}

        ItemInfo(const std::wstring& _identifyer, int _decimal_places)
            : identifyer(_identifyer), decimal_places(_decimal_places)
        {}
    };

    struct OptionSettings
    {
        std::vector<ItemInfo> items_info;     //���м����Ŀ
        ItemInfo& FindItemInfo(const std::wstring& identifyer);     //����identifyer����items_info�ҵ�ItemInfo����

        bool hardware_info_auto_refresh{};              //�����Ϣ�����Ƿ��Զ�ˢ��
        bool show_mouse_tooltip{};
    };

}