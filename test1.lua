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


function moveEntity() 
	myEntity:setVelocity(2, 2);
	myEntity:update(500);
end


-- Alright, it's time to perform experiments with lua here
coroutines = {};

-- maps coroutineIndices to tables of references
referenceCounts = {};

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

-- do NOT forget to wipe the dependency list after a 
-- coroutine index is recycled.
function registerDependency(coroutineIndex, objID)

	if referenceCounts[coroutineIndex] == nil then
		-- create new table, add it.
		local newDependency = { objID };
		newDependency.size = 1;
		referenceCounts[coroutineIndex] = newDependency;
		
	else -- not nil, meaning there was an existing table
		local dependencyList = referenceCounts[coroutineIndex];
		table.insert(dependencyList, objID);
		dependencyList.size = dependencyList.size + 1;
		
		-- Is this necessary? 
		-- referenceCounts[coroutineIndex] = dependencyList;
		-- apparently not.
	end
end

function removeDependency(coroutineIndex, objID)
	local dependencyList = referenceCounts[coroutineIndex];
	if dependencyList ~= nil then
		-- loop through list to find objID
		for i,v in pairs(dependencyList) do
		
			print(i.." " ..v);
			if v == objID then
				table.remove(dependencyList, i);
				return;
			end
		end
	end
end

function clearDependencies(coroutineIndex)

	local dependencyList = referenceCounts[coroutineIndex];
	if dependencyList ~= nil then
	
		for i, v in pairs(dependencyList) do 
			-- v is the dependency
			-- LuaInterface:unregister(v);
			print(v);
		end
	
		referenceCounts[coroutineIndex] = nil;
	end
	
end

registerDependency(0, 55);
registerDependency(0, 22);
registerDependency(1, 38);
registerDependency(1, 89);
registerDependency(1, 109);
removeDependency(0, 22);
--removeDependency(0, 4444);


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