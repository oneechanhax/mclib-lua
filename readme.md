# Mclib-lua 

Bindings for mclib

## Build
```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

## Usage of exports
```lua
require("mclib_lua")

local GetMc = function()
    return {
    block = {
        BlockRegistry = mclib_block_BlockRegistry
    },
    core = {
        Client = mclib_core_Client,
        ClientSettings = mclib_core_ClientSettings,
        Connection = mclib_core_Connection,
        UpdateMethod = mclib_core_UpdateMethod
    },
    protocol = {
        packets = {
            PacketDispatcher = mclib_protocol_packets_PacketDispatcher
        },
    },
    util = {
        PlayerController = mclib_util_PlayerController,
        VersionFetcher = mclib_util_VersionFetcher
    },
    MainHand = mclib_MainHand,
    --GetNode = function()
     --   mclib.get_node(pos.x, pos.y, pos.z)
    --end,
    --GetPlayerPos = function()
    --    return vector.new(mclib.GetPlayerPos())
    --end
    }
end
local mc = GetMc()
```

