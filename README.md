while true do
firetouchinterest(game.Players.LocalPlayer.Character.HumanoidRootPart, game:GetService("Workspace").Parts.Decoration["Healing Pond"].Pad, 0)
task.wait(0.5)
firetouchinterest(game.Players.LocalPlayer.Character.HumanoidRootPart, game:GetService("Workspace").Parts.Decoration["Healing Pond"].Pad, 1)
task.wait(0.5)
end
--speed--fire--
if not getgenv()._origFire then
    local mt = getrawmetatable(game:GetService("ReplicatedStorage").GunShot)
    setreadonly(mt, false)
    getgenv()._origFire = mt.__namecall
end
getgenv().rapidFire = 2  -- change me 
local mt = getrawmetatable(game:GetService("ReplicatedStorage").GunShot)
mt.__namecall = newcclosure(function(self, ...)
    if getnamecallmethod() == "FireServer" and select(1,...) == "shoot" then
        for i = 1, getgenv().rapidFire do getgenv()._origFire(self,...) end
    end
    return getgenv()._origFire(self,...)
end)
