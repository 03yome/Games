----bypass adonis----
local getinfo = getinfo or debug.getinfo
local DEBUG = false
local Hooked = {}

local Detected, Kill

if setthreadidentity then setthreadidentity(2) end

for i, v in getgc(true) do
    if typeof(v) == "table" then
        local DetectFunc = rawget(v, "Detected")
        local KillFunc = rawget(v, "Kill")

        if typeof(DetectFunc) == "function" and not Detected then
            Detected = DetectFunc
            local Old; Old = hookfunction(Detected, function(Action, Info, NoCrash)
                if Action ~= "_" then
                    if DEBUG then
                        warn(`Adonis AntiCheat flagged\nMethod: {Action}\nInfo: {Info}`)
                    end
                end
                return true
            end)
            table.insert(Hooked, Detected)
        end

        if rawget(v, "Variables") and rawget(v, "Process") and typeof(KillFunc) == "function" and not Kill then
            Kill = KillFunc
            local Old; Old = hookfunction(Kill, function(Info)
                if DEBUG then
                    warn(`Adonis AntiCheat tried to kill (fallback): {Info}`)
                end
            end)
            table.insert(Hooked, Kill)
        end
    end
end

local Old; Old = hookfunction(getrenv().debug.info, newcclosure(function(...)
    local LevelOrFunc, Info = ...
    if Detected and LevelOrFunc == Detected then
        if DEBUG then
            warn(`zins | adonis bypassed`)
        end
        return coroutine.yield(coroutine.running())
    end
    return Old(...)
end))

if setthreadidentity then setthreadidentity(7) end
---semni godmode---
local semiGodActive = false
local semiGodHook

local function toggleSemiGod(state)
    if state and not semiGodActive then
        if hookmetamethod then
            semiGodHook = hookmetamethod(game, "__namecall", function(self, ...)
                local args = {...}
                local method = getnamecallmethod()
                if method == "FireServer" and self.Name == "Asynchronous" then
                    if args[1] == "HurtSelf" then
                        args[3] = 0.001 -- nearly zero damage
                    elseif args[1] == "CharHit" then
                        args[4] = "Humanoid"
                    end
                    return semiGodHook(self, unpack(args))
                end
                return semiGodHook(self, ...)
            end)
            semiGodActive = true
            print("Semi God Mode: Đã bật")
        else
            game:GetService("Players").LocalPlayer:Kick("LoL!")
        end
    elseif not state and semiGodActive then
        
        semiGodActive = false
    end
end

local Rayfield = loadstring(game:HttpGet('https://sirius.menu/rayfield'))()

if game.CoreGui:FindFirstChild("Rayfield") then
   game.CoreGui.Rayfield:Destroy()
end

local Window = Rayfield:CreateWindow({
   Name = "S.E.W.H",
   Icon = 0, 
   LoadingTitle = "lol",
   LoadingSubtitle = "Script By romd3976",
   Theme = "DarkBlue", 

   DisableRayfieldPrompts = false,
   DisableBuildWarnings = false,

   ConfigurationSaving = {
      Enabled = true,
      FolderName = "Vietnamvodich", 
      FileName = "ควย" 
   },

   Discord = {
      Enabled = false, 
      Invite = "noinvitelink", 
      RememberJoins = true 
   },

   KeySystem = false, 
   KeySettings = {
      Title = "My rolbox profile 'romd3976'",
      Subtitle = "Key",
      Note = "Key is on the YT", 
      FileName = "Key", 
      SaveKey = true, 
      GrabKeyFromSite = false,
      Key = {"222554"} 
   }
})

local Tab = Window:CreateTab("Main", nil)

local Toggle = Tab:CreateToggle({
   Name = "Anti-Ragdoll",
   CurrentValue = false,
   Flag = "AntiRagdollToggle",
   Callback = function(Value)
       _G.AntiRagdoll = Value
       _G.BlockRemote = Value
   end,
})

-- Tích hợp code gốc vào script
local RunService = game:GetService("RunService")

_G.BlockRemote = false
_G.AntiRagdoll = false

local original
local namecallHook = newcclosure(function(self, ...)
    local method = getnamecallmethod()
    local args = {...}

    if _G.BlockRemote and typeof(self) == "Instance" then
        local success, name = pcall(function() return self.Name end)
        if success then
            if name == "Asynchronous" and (method == "FireServer" or method == "fireServer") then
                local action = args[1]
                if _G.AntiRagdoll and action == "UpdateRagdoll" and args[2] == true then
                    args[2] = false
                    return original(self, unpack(args))
                end
            end
        end
    end

    return original(self, ...)
end)

local function enableHook()
    if hookmetamethod then
        original = hookmetamethod(game, "__namecall", namecallHook)
    else
        local gm = getrawmetatable(game)
        original = gm.__namecall
        setreadonly(gm, false)
        gm.__namecall = namecallHook
        setreadonly(gm, true)
    end
end

enableHook()
RunService.Heartbeat:Connect(function() end)
