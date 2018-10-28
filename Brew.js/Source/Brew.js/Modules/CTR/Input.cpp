#include <Brew.js/Modules/CTR/Input.hpp>

namespace Brew::BuiltIn::Input
{
    API::Function getPressed(API::NativeContext Context)
    {
        API::FunctionHandler handler(Context);
        hidScanInput();
        u64 inp = hidKeysDown();
        handler.ReturnUInt(inp);
        return API::Return::Variable;
    }

    API::Function getHeld(API::NativeContext Context)
    {
        API::FunctionHandler handler(Context);
        u64 inp = hidKeysHeld();
        handler.ReturnUInt(inp);
        return API::Return::Variable;
    }

    API::Function getReleased(API::NativeContext Context)
    {
        API::FunctionHandler handler(Context);
        u64 inp = hidKeysUp();
        handler.ReturnUInt(inp);
        return API::Return::Variable;
    }

    API::Function getTouch(API::NativeContext Context)
    {
        API::FunctionHandler handler(Context);
        hidScanInput();
        u64 inp = hidKeysHeld();
        API::Object obj(Context);
        handler.ReturnObject(obj);
        if(inp & KEY_TOUCH)
        {
            touchPosition tch;
            hidTouchRead(&tch);
            obj.AddUInt("X", tch.px);
            obj.AddUInt("Y", tch.py);
        }
        else
        {
            obj.AddUInt("X", 0);
            obj.AddUInt("Y", 0);
        }
        return API::Return::Variable;
    }

    API::Function getCPadPosition(API::NativeContext Context)
    {
        API::FunctionHandler handler(Context);
        API::Object obj(Context);
        handler.ReturnObject(obj);
        circlePosition tch;
        hidCircleRead(&tch);
        obj.AddUInt("X", tch.dx);
        obj.AddUInt("Y", tch.dy);
        return API::Return::Variable;
    }

    API::Module Initialize()
    {
        API::Module input("input");
        input.PushUInt("A", KEY_A);
        input.PushUInt("B", KEY_B);
        input.PushUInt("Select", KEY_SELECT);
        input.PushUInt("Start", KEY_START);
        input.PushUInt("DPadRight", KEY_DRIGHT);
        input.PushUInt("DPadLeft", KEY_DLEFT);
        input.PushUInt("DPadUp", KEY_DUP);
        input.PushUInt("DPadDown", KEY_DDOWN);
        input.PushUInt("L", KEY_L);
        input.PushUInt("R", KEY_R);
        input.PushUInt("X", KEY_X);
        input.PushUInt("Y", KEY_Y);
        input.PushUInt("ZL", KEY_ZL);
        input.PushUInt("ZR", KEY_ZR);
        input.PushUInt("Touch", KEY_TOUCH);
        input.PushUInt("CStickRight", KEY_CSTICK_RIGHT);
        input.PushUInt("CStickLeft", KEY_CSTICK_UP);
        input.PushUInt("CStickUp", KEY_CSTICK_UP);
        input.PushUInt("CStickDown", KEY_CSTICK_UP);
        input.PushUInt("CPadRight", KEY_CPAD_RIGHT);
        input.PushUInt("CPadLeft", KEY_CPAD_LEFT);
        input.PushUInt("CPadUp", KEY_CPAD_UP);
        input.PushUInt("CPadDown", KEY_CPAD_DOWN);
        input.PushUInt("Up", KEY_UP);
        input.PushUInt("Down", KEY_DOWN);
        input.PushUInt("Left", KEY_LEFT);
        input.PushUInt("Right", KEY_RIGHT);
        input.PushFunction("getPressed", getPressed);
        input.PushFunction("getHeld", getHeld);
        input.PushFunction("getReleased", getReleased);
        input.PushFunction("getTouch", getTouch);
        input.PushFunction("getCPadPosition", getCPadPosition);
        return input;
    }
}