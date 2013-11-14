/*
 Copyright (C) 2010-2012 Kristian Duske
 
 This file is part of TrenchBroom.
 
 TrenchBroom is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 TrenchBroom is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with TrenchBroom. If not, see <http://www.gnu.org/licenses/>.
 */

#include "RecentDocumentListBox.h"

#include "StringUtils.h"
#include "TrenchBroomApp.h"
#include "IO/Path.h"
#include "IO/ResourceUtils.h"
#include "Model/GameConfig.h"
#include "Model/GameFactory.h"
#include "View/RecentDocumentSelectedCommand.h"

#include <cassert>

namespace TrenchBroom {
    namespace View {
        RecentDocumentListBox::RecentDocumentListBox(wxWindow* parent) :
        ImageListBox(parent, wxSize(32, 32)),
        m_documentIcon(IO::loadImageResource(IO::Path("images/DocIcon.png"))) {
            const TrenchBroomApp& app = View::TrenchBroomApp::instance();
            const IO::Path::List& recentDocuments = app.recentDocuments();
            SetItemCount(recentDocuments.size());
            Bind(wxEVT_LISTBOX_DCLICK, &RecentDocumentListBox::OnListBoxDoubleClick, this);
        }

        void RecentDocumentListBox::OnListBoxDoubleClick(wxCommandEvent& event) {
            const TrenchBroomApp& app = View::TrenchBroomApp::instance();
            const IO::Path::List& recentDocuments = app.recentDocuments();

            const int index = GetSelection();
            if (index < 0 || index >= recentDocuments.size())
                return;
            
            const IO::Path& documentPath = recentDocuments[index];
            RecentDocumentSelectedCommand command;
            command.setDocumentPath(documentPath);
            command.SetEventObject(this);
            command.SetId(GetId());
            ProcessEvent(command);
        }

        const wxBitmap& RecentDocumentListBox::image(const size_t n) const {
            return m_documentIcon;
        }
        
        wxString RecentDocumentListBox::title(const size_t n) const {
            const TrenchBroomApp& app = View::TrenchBroomApp::instance();
            const IO::Path::List& recentDocuments = app.recentDocuments();
            assert(n < recentDocuments.size());
            return recentDocuments[n].lastComponent().asString();
        }
        
        wxString RecentDocumentListBox::subtitle(const size_t n) const {
            const TrenchBroomApp& app = View::TrenchBroomApp::instance();
            const IO::Path::List& recentDocuments = app.recentDocuments();
            assert(n < recentDocuments.size());
            return recentDocuments[n].asString();
        }
    }
}