-- Lua Hello World (test.lua)
function helloWorld ()
   return "Hello World\n"
end

function DoAThing(a, b)
    print("[LUA] DoAThing("..a..", "..b..") called\n")
    c = HostFunction(a + 10, b * 3)
    return c
end

function MoveObject()
    print("[LUA] Moving Object");
    MoveSprite(3, 5)
end

function CreateLuaSprite()
    sprite = CreateSprite()
    return sprite
end