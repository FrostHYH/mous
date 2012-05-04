#ifndef PLAYLISTVIEW_H
#define PLAYLISTVIEW_H

#include <ncurses.h>
#include <panel.h>

#include <util/MediaItem.h>
#include <util/Playlist.h>
using namespace mous;

#include "IView.h"

class PlaylistView: public IView
{
public:
    PlaylistView();
    ~PlaylistView();

    void OnResize(int x, int y, int w, int h);
    void Refresh(int x, int y, int w, int h);

    bool InjectKey(int key);

    void Show(bool shown);
    bool IsShown() const;

    void SetFocus(bool focused);
    bool HasFocus() const;

private:
    Playlist<MediaItem*> m_List;
};

#endif
