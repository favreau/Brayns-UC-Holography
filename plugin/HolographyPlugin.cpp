/* Copyright (c) 2020, EPFL/Blue Brain Project
 * All rights reserved. Do not distribute without permission.
 * Responsible Author: Cyrille Favreau <cyrille.favreau@epfl.ch>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "HolographyPlugin.h"

#include <plugin/common/Logs.h>

#include <brayns/common/ActionInterface.h>
#include <brayns/engineapi/Engine.h>
#include <brayns/parameters/ParametersManager.h>
#include <brayns/pluginapi/Plugin.h>

namespace holography
{
using namespace brayns;

const std::string PLUGIN_VERSION = "0.1.0";
const std::string PLUGIN_API_PREFIX = "hg_";

#define CATCH_STD_EXCEPTION()                  \
    catch (const std::runtime_error &e)        \
    {                                          \
        response.status = false;               \
        response.contents = e.what();          \
        PLUGIN_ERROR << e.what() << std::endl; \
    }

void _addHolographicCamera(brayns::Engine &engine)
{
    PLUGIN_INFO << "Registering 'holographic' camera" << std::endl;

    brayns::PropertyMap properties;
    properties.setProperty({"fovy", 45., .1, 360., {"Field of view"}});
    properties.setProperty({"aspect", 1., {"Aspect ratio"}});
    properties.setProperty({"apertureRadius", 0., {"Aperture radius"}});
    properties.setProperty({"focusDistance", 1., {"Focus Distance"}});
    properties.setProperty({"enableClippingPlanes", true, {"Clipping"}});
    properties.setProperty({"stereo", false, {"Stereo"}});
    properties.setProperty({"interpupillaryDistance", 0.0635, 0.0, 10.0, {"Eye separation"}});
    engine.addCameraType("holographic", properties);
}

HolographyPlugin::HolographyPlugin()
    : ExtensionPlugin()
{
}

void HolographyPlugin::init()
{
    auto actionInterface = _api->getActionInterface();
    auto &engine = _api->getEngine();

    if (actionInterface)
    {
        std::string entryPoint = PLUGIN_API_PREFIX + "version";
        PLUGIN_INFO << "Registering '" + entryPoint + "' endpoint" << std::endl;
        actionInterface->registerRequest<Response>(entryPoint, [&]() { return _version(); });
    }

    _addHolographicCamera(engine);
}

Response HolographyPlugin::_version() const
{
    Response response;
    response.contents = PLUGIN_VERSION;
    return response;
}

extern "C" ExtensionPlugin *brayns_plugin_create(int argc, char **argv)
{
    PLUGIN_INFO << std::endl;
    PLUGIN_INFO << "_|_|_|    _|                      _|            _|    _|     "
                   "       _|            "
                << std::endl;
    PLUGIN_INFO << "_|    _|  _|    _|_|_|    _|_|_|  _|  _|        _|    _|    "
                   "_|_|    _|    _|_|    "
                << std::endl;
    PLUGIN_INFO << "_|_|_|    _|  _|    _|  _|        _|_|          _|_|_|_|  _| "
                   "   _|  _|  _|_|_|_|  "
                << std::endl;
    PLUGIN_INFO << "_|    _|  _|  _|    _|  _|        _|  _|        _|    _|  _| "
                   "   _|  _|  _|        "
                << std::endl;
    PLUGIN_INFO << "_|_|_|    _|    _|_|_|    _|_|_|  _|    _|      _|    _|    "
                   "_|_|    _|    _|_|_|  "
                << std::endl;
    PLUGIN_INFO << std::endl;
    PLUGIN_INFO << "Initializing Black Hole plug-in (version " << PLUGIN_VERSION << ")" << std::endl;
    PLUGIN_INFO << std::endl;

    return new HolographyPlugin();
}

} // namespace holography
