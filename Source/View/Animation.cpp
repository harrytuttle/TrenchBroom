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
 along with TrenchBroom.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Animation.h"

#include "Utility/List.h"

#include <wx/app.h>
#include <wx/timer.h>

#include <cassert>

namespace TrenchBroom {
    namespace View {
        Animation::Animation(Curve curve, wxLongLong duration) :
        m_curve(NULL),
        m_duration(duration),
        m_elapsed(0),
        m_progress(0.0) {
            assert(m_duration > 0);
            switch (curve) {
                case EaseInEaseOutCurve:
                    m_curve = new EaseInEaseOutAnimationCurve(m_duration);
                    break;
                default:
                    m_curve = new FlatAnimationCurve();
                    break;
            }
        }

        Animation::~Animation() {
            delete m_curve;
            m_curve = NULL;
        }

        bool Animation::step(wxLongLong delta) {
            wxCriticalSectionLocker lock(m_lock);
            m_elapsed = std::min(m_elapsed + delta, m_duration);
            m_progress = m_elapsed.ToDouble() / m_duration.ToDouble();
            return m_elapsed >= m_duration;
        }

        void Animation::update() {
            wxCriticalSectionLocker lock(m_lock);
            doUpdate(m_progress);
        }

        void AnimationExecutable::execute() {
            Animation::List::const_iterator it, end;
            for (it = m_animations.begin(), end = m_animations.end(); it != end; ++it) {
                Animation& animation = **it;
                animation.update();
            }
        }

        AnimationExecutable::AnimationExecutable(const Animation::List& animations) :
        m_animations(animations) {}

        wxThread::ExitCode AnimationManager::Entry() {
            m_lastTime = wxGetLocalTimeMillis();
            while (!TestDestroy()) {
                wxLongLong elapsed = wxGetLocalTimeMillis() - m_lastTime;
                Animation::List updateAnimations;
                {
                    wxCriticalSectionLocker lockAnimations(m_animationsLock);
                    if (!m_animations.empty()) {
                        AnimationMap::iterator mapIt = m_animations.begin();
                        while (mapIt != m_animations.end()) {
                            Animation::List& list = mapIt->second;
                            Animation::List::iterator listIt = list.begin();
                            while (listIt != list.end()) {
                                Animation::Ptr animation = *listIt;
                                if (animation->step(elapsed))
                                    listIt = list.erase(listIt);
                                updateAnimations.push_back(animation);
                                if (listIt != list.end())
                                    ++listIt;
                            }

                            if (list.empty())
                                m_animations.erase(mapIt++);
                            else
                                ++mapIt;
                        }
                    }
                }
                m_lastTime += elapsed;

                ExecutableEvent::Executable::Ptr executable(new AnimationExecutable(updateAnimations));
                wxTheApp->QueueEvent(new ExecutableEvent(executable));
                Sleep(20);
            }

            return (wxThread::ExitCode)0;
        }

        AnimationManager::AnimationManager() :
        wxThread(wxTHREAD_DETACHED) {
            Create();
            Run();
        }
    }
}
