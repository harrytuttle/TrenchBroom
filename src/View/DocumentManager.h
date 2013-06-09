/*
 Copyright (C) 2010-2013 Kristian Duske
 
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
 along with TrenchBroom.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __TrenchBroom__DocumentManager__
#define __TrenchBroom__DocumentManager__

#include "View/MapDocument.h"

#include <vector>

namespace TrenchBroom {
    namespace IO {
        class Path;
    }

    namespace View {
        typedef std::vector<MapDocument::Ptr> DocumentList;

        class DocumentManager {
        private:
            bool m_singleDocument;
            DocumentList m_documents;
        public:
            DocumentManager(const bool singleDocument);
            ~DocumentManager();
            
            const DocumentList& documents() const;
            
            MapDocument::Ptr newDocument();
            MapDocument::Ptr openDocument(const IO::Path& path);
            bool closeDocument(MapDocument::Ptr document);
            bool closeAllDocuments();
        private:
            MapDocument::Ptr createOrReuseDocument();
        };
    }
}

#endif /* defined(__TrenchBroom__DocumentManager__) */