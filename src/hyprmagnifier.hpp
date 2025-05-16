#pragma once

#include "defines.hpp"
#include "helpers/LayerSurface.hpp"
#include "helpers/PoolBuffer.hpp"

enum eMoveType {
    MOVE_CORNER = 0,
    MOVE_CURSOR
};

class CHyprmagnifier {
  public:
    void                                        init();

    std::mutex                                  m_mtTickMutex;

    SP<CCWlCompositor>                          m_pCompositor;
    SP<CCWlRegistry>                            m_pRegistry;
    SP<CCWlShm>                                 m_pSHM;
    SP<CCZwlrLayerShellV1>                      m_pLayerShell;
    SP<CCZwlrScreencopyManagerV1>               m_pScreencopyMgr;
    SP<CCWpCursorShapeManagerV1>                m_pCursorShapeMgr;
    SP<CCWpCursorShapeDeviceV1>                 m_pCursorShapeDevice;
    SP<CCWlSeat>                                m_pSeat;
    SP<CCWlKeyboard>                            m_pKeyboard;
    SP<CCWlPointer>                             m_pPointer;
    SP<CCWpFractionalScaleManagerV1>            m_pFractionalMgr;
    SP<CCWpViewporter>                          m_pViewporter;
    wl_display*                                 m_pWLDisplay = nullptr;
    SP<CCWlSurface>                             m_pWLSurface;

    xkb_context*                                m_pXKBContext = nullptr;
    xkb_keymap*                                 m_pXKBKeymap  = nullptr;
    xkb_state*                                  m_pXKBState   = nullptr;

    bool                                        m_bRenderInactive    = false;
    bool                                        m_bNoFractional      = false;
    bool                                        m_bDisableHexPreview = true;
    bool                                        m_bUseLowerCase      = false;

    double                                      m_dZoom = 0.5;

    bool                                        m_bRunning = true;

    eMoveType                                   m_eMoveType = MOVE_CURSOR;

    std::vector<std::unique_ptr<SMonitor>>      m_vMonitors;
    std::vector<std::unique_ptr<CLayerSurface>> m_vLayerSurfaces;

    CLayerSurface*                              m_pLastSurface;

    Vector2D                                    m_vLastCoords;
    Vector2D                                    m_vPosition;
    Vector2D                                    m_vSize = Vector2D(300, 150);

    void                                        renderSurface(CLayerSurface*, bool forceInactive = false);

    int                                         createPoolFile(size_t, std::string&);
    bool                                        setCloexec(const int&);
    void                                        recheckACK();
    void                                        initKeyboard();
    void                                        initMouse();

    SP<SPoolBuffer>                             getBufferForLS(CLayerSurface*);

    void                                        convertBuffer(SP<SPoolBuffer>);
    void*                                       convert24To32Buffer(SP<SPoolBuffer>);

    void                                        markDirty();

    void                                        finish(int code = 0);

  private:
};

inline std::unique_ptr<CHyprmagnifier> g_pHyprmagnifier;
