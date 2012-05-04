#include "HelpView.h"

#include <algorithm>

const char* const STR_ARRAY[] = 
{
    "",

    "^b==== Shortcut ====",
    "",

    "^bGlobal Window:",
    "H      show/hide help",
    "E      show/hide file explorer",
    "q      quit",
    "Q      quit and stop server",
    "0      switch to temporary playlist",
    "1-5    switch to user playlist",
    "",
    "SPACE  pause/resume",
    "P      play previous one",
    "N      play next one",
    "",
    "TAB    switch focus between file explorer/playlist",
    "",

    "^bFile Explorer View:",
    "k      scroll up",
    "j      scroll down",
    "h      to parent dir",
    "l      enter dir",
    "ENTER  open item in temporary playlist",
    "a      add item to current playlist",
    "",

    "^bPlaylist View:",
    "k      scroll up",
    "j      scroll down",
    "h      show previous playlist",
    "l      show next playlist",
    "d      remove item",
    "c      cut item and put it into queue",
    "y      copy item and put it into queue",
    "p      paste the first item of queue to next line",
    "C      clear queue",
    "",

    "^bHelp View:",
    "k      scroll up",
    "j      scroll down",
    "",

    "^b==== About ====",
    "Since:     2012.02.11",
    "License:   New BSD License",
    "Author:    Yanhui Shen <shen.elf@gmail.com>",
    ""
};

HelpView::HelpView():
    m_LineBegin(0),
    m_LineCount(sizeof(STR_ARRAY)/sizeof(STR_ARRAY[0]))
{
}

HelpView::~HelpView()
{
}

void HelpView::OnResize(int x, int y, int w, int h)
{
    d.Cleanup();
    d.Init(x, y, w, h);
}

void HelpView::Refresh()
{
    d.Clear();

    d.CenterPrint(0, "^b[Help]");
    for (int l = 0; l < d.height-2 && l < m_LineCount - m_LineBegin; ++l) {
        int index = m_LineBegin+l;
        d.Print(8, l+1, STR_ARRAY[index]);
    }

    d.Refresh();
}

void HelpView::MoveTo(int x, int y)
{
    d.MoveTo(x, y);
}

void HelpView::Resize(int w, int h)
{
    d.Resize(w, h);
}

bool HelpView::InjectKey(int key)
{
    switch (key) {
        case 'j':
            if (m_LineBegin < m_LineCount-(d.height-2))
                ++m_LineBegin;
            break;

        case 'k':
            if (m_LineBegin > 0)
                --m_LineBegin;
            break;

        default:
            return false;
    }
    Refresh();
    return true;
}

void HelpView::Show(bool show)
{
    d.Show(show);
}

bool HelpView::IsShown() const
{
    return d.shown;
}