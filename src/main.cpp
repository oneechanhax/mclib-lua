
#include "mclib/common/Vector.h"
#include "mclib/protocol/ProtocolState.h"
#include "mclib/world/World.h"
#include <exception>
#include <iostream>
#include <mclib/common/Common.h>
#include <mclib/core/Client.h>
#include <mclib/util/Forge.h>
#include <mclib/util/Hash.h>
#include <mclib/util/Utility.h>
#include <mclib/util/VersionFetcher.h>
#include <luaaa.hpp>
#include <memory>
#include <optional>
#include <chrono>
#include <stdexcept>
#include <thread>
// https://cs.brynmawr.edu/Courses/cs380/fall2011/luar-topics2.pdf
// https://github.com/gengyong/luaaa
//
#ifdef __cplusplus
extern "C" {
#endif

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#ifdef __cplusplus
}
#endif

namespace mc::lua {

class McLib {
private:
    /*class ChunkPacketHandler : public protocol::packets::PacketHandler, public core::ClientListener, public world::WorldListener {
    private:
        McLib* parent;

    public:
        ChunkPacketHandler(McLib* parent)
            : parent(parent)
            , mc::protocol::packets::PacketHandler(&parent->dispatcher) {
            assert(parent);
            parent->client->GetWorld()->RegisterListener(this);
        }
        ~ChunkPacketHandler() {
            parent->client->GetWorld()->RegisterListener(this);
        }
        virtual void OnChunkLoad(world::ChunkPtr chunk, const world::ChunkColumnMetadata& meta, u16 yIndex) override {
            // this->parent.
        }
        virtual void OnChunkUnload(world::ChunkColumnPtr chunk) override {
        }
        virtual void OnBlockChange(Vector3i position, block::BlockPtr newBlock, block::BlockPtr oldBlock) override {
        }
    };*/

public:
    /*void Load() {
        if (!version)
            this->version = util::VersionFetcher(server, port).GetVersion();
        mc::block::BlockRegistry::GetInstance()->RegisterVanillaBlocks(*this->version);

        this->client.emplace(&this->dispatcher, *this->version);
        client->GetPlayerController()->SetHandleFall(true);
        client->GetConnection()->GetSettings().SetMainHand(mc::MainHand::Right).SetViewDistance(this->view_distance);

        // try {
        client->Login(this->server, this->port, this->username, this->password, mc::core::UpdateMethod::Threaded);
        //} catch (...) { }
        return;
    }
    void SetServer(std::string v) {
        this->server = v;
    }
    void SetPort(int v) {
        this->port = v;
    }
    void SetLogin(std::string v) {
        this->username = v;
    }
    u32 GetNode(double x, double y, double z) {
        auto block = client->GetWorld()->GetBlock(mc::Vector3d(x, y, z));
        return block->GetType();
    };
    bool IsLoaded() {
        return this->client.has_value();
    }

private:
    std::optional<core::Client> client;
    protocol::packets::PacketDispatcher dispatcher;
    std::string server = "127.0.0.1";
    u16 port = 25565;
    std::string username = "testplayer";
    std::string password;
    int view_distance = 8;
    const bool useProfileToken = false;
    std::optional<protocol::Version> version = protocol::Version::Minecraft_1_12_2; // Should this be def?
    */
    // class Util {

    //}
};

/*static int mclib_get_node(lua_State* L) {
    }*/

/*static int mclib_get_player_pos(lua_State* L) {
    auto pos = client->GetPlayerController()->GetPosition();
    lua_pushinteger(L, pos.x);
    lua_pushinteger(L, pos.y);
    lua_pushinteger(L, pos.z);
    return 3;
}*/

/*static std::optional<McLib> mclib_singleton;
static const luaL_Reg lua_exports[] = {
    { "new", [](lua_State* L) -> int {
         if (!mclib_singleton) {
             mclib_singleton.emplace();
             return 0;
         }
         if (mclib_singleton->IsLoaded()) {
             lua_pushstring(L, "mclib-lua can only support one instance at a time due to technical limintations!");
             lua_error(L);
             return 1;
         }
         return 0;
     } },
    { "Load", [](lua_State* L) -> int {
         try {
             mclib_singleton->Load();
         } catch (const std::exception& err) {
             lua_pushstring(L, err.what());
             lua_error(L);
             return 1;
         }
         return 0;
     } },
    { "GetNode", [](lua_State* L) -> int {
         double x = luaL_checknumber(L, 1); // get item 1
         double y = luaL_checknumber(L, 2);
         double z = luaL_checknumber(L, 3);
         auto block_id = mclib_singleton->GetNode(x, y, z);
         // lua_pushnumber(L, block_id.c_str(), block_id.size());
         return 0; // number of items returned
     } },*/
/*{ "get_player_pos", mclib_get_player_pos },*/ //{ NULL, NULL }
//};

} // namespace mc::lua

/*namespace luaaa {
using namespace mc;
template <>
struct LuaStack<util::VersionFetcher> {
    inline static void put(lua_State* L, const Position& v) {
        lua_newtable(L);
        LuaStack<const char*>::put(L, "x");
        LuaStack<float>::put(L, v.x);
        lua_rawset(L, -3);
        LuaStack<const char*>::put(L, "y");
        LuaStack<float>::put(L, v.y);
        lua_rawset(L, -3);
        LuaStack<const char*>::put(L, "z");
        LuaStack<float>::put(L, v.z);
        lua_rawset(L, -3);
    }
};
} */
// namespace luaaa

class McLib {
};

namespace luaaa {
template <>
struct LuaStack<mc::protocol::Version> {
    inline static mc::protocol::Version get(lua_State* L, int idx) {
        return mc::protocol::Version(LuaStack<int>::get(L, idx));
    }

    inline static void put(lua_State* L, const mc::protocol::Version& v) {
        LuaStack<int>::put(L, (int)v);
    }
};

} // namespace luaaa

namespace mc {
using namespace luaaa;

namespace block {
void BindToLua(lua_State* L) {
    LuaModule br(L, "mclib_block_BlockRegistry");
    br.fun("RegisterVanillaBlocks", [](protocol::Version protocolVersion) { BlockRegistry::GetInstance()->RegisterVanillaBlocks(protocolVersion); });
}
} // namespace block

namespace core {
void BindToLua(lua_State* L) {
    LuaModule client(L, "mclib_core_Client");
    client.fun("new", [](protocol::packets::PacketDispatcher* pd, protocol::Version v) {
        return new Client(pd, v);
    });
    client.fun("Login", [](Client* this_ptr, std::string host, int port, std::string user, std::string password) -> bool {
        return this_ptr->Login(host, port, user, password, UpdateMethod::Threaded);
    });
    client.fun("GetPlayerControllerPtr", [](Client* this_ptr) {
        return this_ptr->GetPlayerController();
    });
    client.fun("GetConnectionPtr", [](Client* this_ptr) {
        return this_ptr->GetConnection();
    });
    // client.fun("Login", &Client::Login);

    LuaModule client_settings(L, "mclib_core_ClientSettings");
    client_settings.fun("SetMainHand", [](ClientSettings* this_ptr, int v) -> void { this_ptr->SetMainHand((MainHand)v); });
    client_settings.fun("SetViewDistance", [](ClientSettings* this_ptr, int v) -> void { this_ptr->SetViewDistance(v); });

    LuaModule connect(L, "mclib_core_Connection");
    // connect.ctor<Connection*>();
    connect.fun("GetSettingsPtr", [](Connection* this_ptr) { return &this_ptr->GetSettings(); });

    LuaModule update_method(L, "mclib_core_UpdateMethod");
    update_method.def("Block", (int)UpdateMethod::Block);
    update_method.def("Threaded", (int)UpdateMethod::Threaded);
    update_method.def("Manual", (int)UpdateMethod::Manual);
    printf("Got: %i\n", (int)UpdateMethod::Threaded);
}
} // namespace core

namespace protocol::packets {
void BindToLua(lua_State* L) {
    LuaModule pd(L, "mclib_protocol_packets_PacketDispatcher");
    pd.fun("new", []() {
        return new PacketDispatcher();
    });
    // pd.fun("GetVersion", &VersionFetcher::GetVersion);
}
} // namespace protocol::packets

namespace util {
void BindToLua(lua_State* L) {
    LuaModule pc(L, "mclib_util_PlayerController");
    pc.fun("SetHandleFall", [](PlayerController* this_ptr, bool v) {
        this_ptr->SetHandleFall(v);
    });
    pc.fun("GetPosition", [](PlayerController* this_ptr) -> std::array<double, 3> {
        auto pos = this_ptr->GetPosition();
        return { pos.x, pos.y, pos.z };
    });

    LuaClass<VersionFetcher> vfetcher(L, "mclib_util_VersionFetcher");
    vfetcher.ctor<std::string, int>();
    vfetcher.fun("GetVersion", &VersionFetcher::GetVersion);
}
} // namespace util

} // namespace mc

extern "C" int luaopen_mclib_lua(lua_State* L) {
    luaaa::LuaModule exports(L, "mclib_lua");
    luaaa::LuaModule main_hand(L, "mclib_MainHand");
    main_hand.def("Right", (int)mc::MainHand::Right);
    main_hand.def("Left", (int)mc::MainHand::Left);

    mc::block::BindToLua(L);
    mc::core::BindToLua(L);
    mc::protocol::packets::BindToLua(L);
    mc::util::BindToLua(L);
    // luaaa::LuaModule exports(L, "mclib_lua_Core");
    // exports.fun("new_core_Client", []() { return "Hllp"; });

    // luaL_register(L, "mclib_lua", mc::lua::lua_exports);
    return 1;
}
//} // namespace mclua
