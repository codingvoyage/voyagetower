function testCoroutine(selfIndex)
	spawnx = 50;
	spawny = -25;
	
	-- I think the issue is that if we resume
	-- then yield a coroutine from within a coroutine,
	-- something ends up going wrong.
	local o;
	local i;
	for j=1,20,1 do
		print(i);
		o = LuaInterface:newEntity(spawnx, spawny, 0, 0);
		i = LuaInterface:newThread("entity");
		
		--LuaInterface:startCoroutine(index, index, objID);
		resumeCoroutine(i, i, o);

		LuaInterface:wait(selfIndex, 1500);
		coroutine.yield();
	end
end

function entity(selfIndex, objID)
	local distance1 = 350;
	local distance2 = 100;
	local speed = 100;
	
	dirMove(selfIndex, objID, "DOWN", speed, 385);
	
	for j=1,10,1 do
		dirMove(selfIndex, objID, "RIGHT", speed, distance2);
		dirMove(selfIndex, objID, "UP", speed, distance1);
		dirMove(selfIndex, objID, "RIGHT", speed, distance2);
		dirMove(selfIndex, objID, "DOWN", speed, distance1);
	end
	
end

function dirMove(callback, objID, direction, speed, distance)
	
	if direction == "UP" then
		move(callback, objID, 0, -1, speed, distance)	
	elseif direction == "DOWN" then
		move(callback, objID, 0, 1, speed, distance)
	elseif direction == "LEFT" then
		move(callback, objID, -1, 0, speed, distance)
	elseif direction == "RIGHT" then
		move(callback, objID, 1, 0, speed, distance)
	else
		print("Incorrect direction");
	end
end

function move(callback, objID, ux, uy, speed, distance)
	-- first, make ux and uy into a unit vector
	local magnitude = math.sqrt(ux*ux + uy*uy);
	local ux = ux/magnitude;
	local uy = uy/magnitude;
	local vx = ux*speed;
	local vy = uy*speed;
	
	LuaInterface:moveEntity(callback, objID
		, vx, vy, distance);
	coroutine.yield();
end


--[[
function entity(selfIndex, objID)
	coroutine.yield();
	LuaInterface:moveEntity(selfIndex, objID --0
		, 0, 50, 150);
	print("ended.");
end
]]--

function moveEntity() 
	myEntity:setVelocity(2, 2);
	myEntity:update(500);
end

function asdf123(selfIndex)
	
	
	--LuaInterface:boop();
	print(55);
	print("Self index: "..selfIndex);
	
	-- Pause before going
	LuaInterface:wait(selfIndex, 2000);
	coroutine.yield();
	
	print("Going now");
	
	objID = LuaInterface:newEntity(0, 0, 0, 0);
	LuaInterface:moveEntity(selfIndex, objID --0
		, 100, 50, 500);
	coroutine.yield();
	
	print("Done.");
	--coroutine.yield();
	
	--index = LuaInterface:newThread("secondCoroutine");
	--print(index);
	
	--while (true) do
	--	resumeCoroutine(index, selfIndex);
	--	LuaInterface:wait(selfIndex, 1);
	--	coroutine.yield();
	--end
	
	--[[newVel = 2;
	
    for i=1,100,1 do 
		newVel = newVel + 0.5;
		myEntity:setVelocity(newVel, newVel);
		myEntity:update(50);
		coroutine.yield();
		--print(i) 
	end ]]--
end	

-- moveEntity(coroutineIndex, objID, vx, vy, distance)
function secondCoroutine(selfIndex)
	
	----LuaInterface:moveEntity(selfIndex, 0
	--	, 100, 50, 500);
	--coroutine.yield();
	--[[newVel = 2;
	
    for i=1,100,1 do 
		newVel = newVel + 0.5;
		myEntity:setVelocity(newVel, newVel);
		myEntity:update(50);
		coroutine.yield();
		--print(i) 
	end
]]--
end

-- Alright, it's time to perform experiments with lua here

coroutines = {};
index = 1;
function newCoroutine(funcName)
	--co = coroutine.create( testCoroutine);
	co = coroutine.create( _G[funcName] );
	--coroutine.resume(co);
	coroutines[index] = co;
	index = index + 1;
	return index - 1;
end

function startCoroutine(funcName, ...)
	coIndex = newCoroutine(funcName);
	resumeCoroutine(coIndex, ...)
end

function resumeCoroutine(coroutineIndex, ...)
	-- get coroutine.
	co = coroutines[coroutineIndex];
	--print(coroutine.status(co));
	--local results = coroutine.resume(co, ...);
	--local results =  coroutine.resume(co, ...) 
	--return results; 
	--a, b, c = coroutine.resume(co, ...);
	--print("resultados:");
	--print(a);
	--print(b);
	--print(c);
	return coroutine.resume(co, ...);
	--return a, b;
end


function getCoroutineStatus(index)
	co = coroutines[index];
	status = coroutine.status(co);
	
	if (status == "running") then 
		return 0;
	elseif (status == "normal") then
		return 0;
	elseif (status == "suspended") then
		return 1;
	elseif (status == "dead") then 
		return -1;
	end
	
end