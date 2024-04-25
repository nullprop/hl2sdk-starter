#pragma once

#include "eiface.h"
#include "icvar.h"
#include "IEngineTrace.h"
#include "igameevents.h"
#include "iplayerinfo.h"
#include "iserverplugin.h"
#include "vstdlib/random.h"

struct EngineInterfaces
{
    EngineInterfaces() :
        cvar(nullptr),
        engineServer(nullptr),
        engineTrace(nullptr),
        gameEventManager(nullptr),
        serverPluginHelpers(nullptr),
        uniformRandomStream(nullptr),

        botManager(nullptr),
        playerInfoManager(nullptr),
        globalVars(nullptr)
    {
    }

    EngineInterfaces(CreateInterfaceFn engineFactory, CreateInterfaceFn serverFactory) :
        EngineInterfaces()
    {
        // Engine interfaces
        cvar         = (ICvar*)engineFactory(CVAR_QUERY_INTERFACE_VERSION, NULL);
        engineServer = (IVEngineServer*)engineFactory(INTERFACEVERSION_VENGINESERVER, NULL);
        engineTrace  = (IEngineTrace*)engineFactory(INTERFACEVERSION_ENGINETRACE_SERVER, NULL);
        gameEventManager =
            (IGameEventManager2*)engineFactory(INTERFACEVERSION_GAMEEVENTSMANAGER2, NULL);
        serverPluginHelpers =
            (IServerPluginHelpers*)engineFactory(INTERFACEVERSION_ISERVERPLUGINHELPERS, NULL);
        uniformRandomStream =
            (IUniformRandomStream*)engineFactory(VENGINE_SERVER_RANDOM_INTERFACE_VERSION, NULL);

        // Server interfaces
        botManager = (IBotManager*)serverFactory(INTERFACEVERSION_PLAYERBOTMANAGER, NULL);
        playerInfoManager =
            (IPlayerInfoManager*)serverFactory(INTERFACEVERSION_PLAYERINFOMANAGER, NULL);
        if (playerInfoManager)
        {
            globalVars = playerInfoManager->GetGlobalVars();
        }
    }

    bool IsValid()
    {
        return cvar && engineServer && engineTrace && gameEventManager && serverPluginHelpers
               && uniformRandomStream && botManager && playerInfoManager;
    }

    void Print()
    {
        Msg("Engine interfaces:\n"
            "   cvar: %p\n"
            "   engineServer: %p\n"
            "   engineTrace: %p\n"
            "   gameEventManager: %p\n"
            "   serverPluginHelpers: %p\n"
            "   uniformRandomStream: %p\n"
            "Server interfaces:\n"
            "   botManager: %p\n"
            "   playerInfoManager: %p\n",
            cvar,
            engineServer,
            engineTrace,
            gameEventManager,
            serverPluginHelpers,
            uniformRandomStream,
            botManager,
            playerInfoManager);
    }

    ICvar*                cvar;
    IVEngineServer*       engineServer;
    IEngineTrace*         engineTrace;
    IGameEventManager2*   gameEventManager;
    IServerPluginHelpers* serverPluginHelpers;
    IUniformRandomStream* uniformRandomStream;

    IBotManager*        botManager;
    IPlayerInfoManager* playerInfoManager;
    CGlobalVars*        globalVars;
};

class ServerPlugin : public IServerPluginCallbacks, IGameEventListener2
{
  public:
    // IServerPluginCallbacks interface
    bool Load(CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory) override;
    void Unload() override;
    void Pause() override;
    void UnPause() override;
    const char* GetPluginDescription() override;
    void        LevelInit(const char* pMapName) override;
    ;
    void          ServerActivate(edict_t* pEdictList, int edictCount, int clientMax) override;
    void          GameFrame(bool simulating) override;
    void          LevelShutdown() override;
    void          ClientPutInServer(edict_t* pEntity, const char* playername) override;
    void          SetCommandClient(int index) override;
    void          ClientActive(edict_t* pEntity) override;
    void          ClientDisconnect(edict_t* pEntity) override;
    void          ClientSettingsChanged(edict_t* pEdict) override;
    PLUGIN_RESULT ClientConnect(
        bool*       bAllowConnect,
        edict_t*    pEntity,
        const char* pszName,
        const char* pszAddress,
        char*       reject,
        int         maxrejectlen
    ) override;
    PLUGIN_RESULT ClientCommand(edict_t* pEntity, const CCommand& args) override;
    PLUGIN_RESULT NetworkIDValidated(const char* pszUserName, const char* pszNetworkID) override;
    void          OnQueryCvarValueFinished(
                 QueryCvarCookie_t     iCookie,
                 edict_t*              pPlayerEntity,
                 EQueryCvarValueStatus eStatus,
                 const char*           pCvarName,
                 const char*           pCvarValue
             ) override;

    // IGameEventListener2 interface
    void FireGameEvent(IGameEvent* event) override;

    void ListenToGameEvent(const char* name);

  private:
    EngineInterfaces m_engineInterfaces;
    int              m_iClientCommandIndex;
    bool             m_gameEventsHooked;
};

extern ServerPlugin g_ServerPlugin;
