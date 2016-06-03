cdpDir = "C:/Users/Logan/Desktop/Sound_Programs/cdpr7/_cdp/_cdprogs/"
workingDir = "E:/Sound/Workspace"

local _0, _1, _2 = ...

mod0 = _0 
mod1 = _1
mod2 = _2

for i=0, 10, 1 do --cross modulates in a cyclic fashion
	mod0 = cdp( "modify", "radical 6", _0, mod2, "$" )
	mod1 = cdp( "modify", "radical 6", _1, mod0, "$" )
	mod2 = cdp( "modify", "radical 6", _2, mod1, "$" )
	mod0 = cdp( "modify", "loudness 3", mod0, "$" )
	mod1 = cdp( "modify", "loudness 3", mod1, "$" )
	mod2 = cdp( "modify", "loudness 3", mod2, "$" )
end

move stuff to github, figure out how to make it easy to do that

return mod0, mod1, mod2