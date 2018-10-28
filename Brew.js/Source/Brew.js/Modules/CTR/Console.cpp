#include <Brew.js/Modules/CTR/Console.hpp>

namespace Brew::BuiltIn::Console
{
    bool cinit = false;
    PrintConsole topc;
    PrintConsole subc;

    API::Function init(API::NativeContext Context)
    {
        API::FunctionHandler handler(Context);
        if(!cinit)
        {
            gfxInitDefault();
            consoleInit(GFX_TOP, &topc);
            consoleInit(GFX_BOTTOM, &subc);
            u32 scr = 0;
            if(handler.CheckArgcEqualOrBigger(1)) scr = handler.GetUInt(0);
            if(scr == 0) consoleSelect(&topc);
            else consoleSelect(&subc);
            cinit = true;
        }
        return API::Return::Void;
    }

    API::Function print(API::NativeContext Context)
    {
        API::FunctionHandler handler(Context);
        if(handler.CheckArgcEqualOrBigger(1) && cinit)
        {
            u32 arg = handler.GetArgc();
            for(u32 i = 0; i < arg; i++)
            {
                if(handler.CheckArgumentType(i, API::Type::String))
                {
                    string arg = handler.GetString(i);
                    cout << arg;
                }
                else if(handler.CheckArgumentType(i, API::Type::Number))
                {
                    double arg = handler.GetDouble(i);
                    stringstream strm;
                    strm << arg;
                    cout << strm.str();
                }
                else if(handler.CheckArgumentType(i, API::Type::Boolean))
                {
                    bool arg = handler.GetBoolean(i);
                    string sbool = (arg ? "true" : "false");
                    cout << sbool;
                }
                else if(handler.CheckArgumentType(i, API::Type::ObjectArray))
                {
                    duk_json_encode(Context, i);
                    cout << duk_to_string(Context, -1);
                }
                else if(handler.CheckArgumentType(i, API::Type::Undefined)) cout << "undefined";
                else if(handler.CheckArgumentType(i, API::Type::Null)) cout << "null";
            }
        }
        return API::Return::Void;
    }

    API::Function trace(API::NativeContext Context)
    {
        API::FunctionHandler handler(Context);
        if(handler.CheckArgcEqualOrBigger(1) && cinit)
        {
            u32 arg = handler.GetArgc();
            cout << "Trace: ";
            for(u32 i = 0; i < arg; i++)
            {
                if(handler.CheckArgumentType(i, API::Type::String))
                {
                    string arg = handler.GetString(i);
                    cout << arg;
                }
                else if(handler.CheckArgumentType(i, API::Type::Number))
                {
                    double arg = handler.GetDouble(i);
                    stringstream strm;
                    strm << arg;
                    cout << strm.str();
                }
                else if(handler.CheckArgumentType(i, API::Type::Boolean))
                {
                    bool arg = handler.GetBoolean(i);
                    string sbool = (arg ? "true" : "false");
                    cout << sbool;
                }
                else if(handler.CheckArgumentType(i, API::Type::ObjectArray))
                {
                    duk_json_encode(Context, i);
                    cout << duk_to_string(Context, -1);
                }
                else if(handler.CheckArgumentType(i, API::Type::Undefined)) cout << "undefined";
                else if(handler.CheckArgumentType(i, API::Type::Null)) cout << "null";
            }
        }
        return API::Return::Void;
    }

    API::Function clear(API::NativeContext Context)
    {
        if(cinit) cout << "\x1b[2J";
        return API::Return::Void;
    }

    API::Function select(API::NativeContext Context)
    {
        API::FunctionHandler handler(Context);
        if(handler.CheckArgcEqualOrBigger(1))
        {
            u32 scr = handler.GetUInt(0);
            if(scr == 0) consoleSelect(&topc);
            else consoleSelect(&subc);
        }
        return API::Return::Void;
    }

    API::Function refresh(API::NativeContext Context)
    {
        if(cinit)
        {
            gfxFlushBuffers();
            gfxSwapBuffers();
            gspWaitForVBlank();
        }
        return API::Return::Void;
    }

    API::Function exit(API::NativeContext Context)
    {
        if(cinit)
        {
            gfxExit();
            cinit = false;
        }
        return API::Return::Void;
    }

    API::Module Initialize()
    {
        API::Module console("console");
        console.PushUInt("Top", 0);
        console.PushUInt("Bottom", 1);
        console.PushFunction("init", init);
        console.PushFunction("log", print);
        console.PushFunction("warn", print);
        console.PushFunction("error", print);
        console.PushFunction("info", print);
        console.PushFunction("debug", print);
        console.PushFunction("trace", trace);
        console.PushFunction("clear", clear);
        console.PushFunction("select", select);
        console.PushFunction("refresh", refresh);
        console.PushFunction("exit", exit);
        return console;
    }
}