#include <strings.h>

#include <iostream>

#include "hyprmagnifier.hpp"

static void help() {
    std::cout << "Hyprmagnifier usage: hyprmagnifier [arg [...]].\n\nArguments:\n"
              << " -h | --help                | Show this help message\n"
              << " -m | --move-type           | Specifies the magnifier move type (corner, cursor)\n"
              << " -s | --size                | Specifies the size of the magnifier (WIDTHxHEIGHT)\n"
              << " -r | --render-inactive     | Render (freeze) inactive displays\n"
              << " -q | --quiet               | Disable most logs (leaves errors)\n"
              << " -v | --verbose             | Enable more logs\n"
              << " -t | --no-fractional       | Disable fractional scaling support\n"
              << " -V | --version             | Print version info\n";
}

int main(int argc, char** argv, char** envp) {
    g_pHyprmagnifier = std::make_unique<CHyprmagnifier>();

    while (true) {
        int                  option_index   = 0;
        static struct option long_options[] = {{"move-type", required_argument, nullptr, 'm'},
                                               {"size", required_argument, nullptr, 's'},
                                               {"help", no_argument, nullptr, 'h'},
                                               {"render-inactive", no_argument, nullptr, 'r'},
                                               {"no-fractional", no_argument, nullptr, 't'},
                                               {"quiet", no_argument, nullptr, 'q'},
                                               {"verbose", no_argument, nullptr, 'v'},
                                               {"version", no_argument, nullptr, 'V'},
                                               {nullptr, 0, nullptr, 0}};

        int                  c = getopt_long(argc, argv, ":f:hnarzqvtdlV", long_options, &option_index);
        if (c == -1)
            break;

        switch (c) {
            case 'm':
                if (strcasecmp(optarg, "corner") == 0)
                    g_pHyprmagnifier->m_eMoveType = MOVE_CORNER;
                else if (strcasecmp(optarg, "cursor") == 0)
                    g_pHyprmagnifier->m_eMoveType = MOVE_CURSOR;
                else {
                    Debug::log(NONE, "Unrecognized format %s", optarg);
                    exit(1);
                }
                break;
            case 's': {
                std::string arg = optarg;
                auto pos = arg.find('x');
                if (pos == std::string::npos) {
                    Debug::log(NONE, "Wrong size format: \"%s\". Must be: WIDTHxHEIGHT", optarg);
                    exit(1);
                }
                std::string strwidth = arg.substr(0, pos);
                std::string strheight = arg.substr(pos + 1);

                try {
                    int width = std::stoi(strwidth);
                    int height = std::stoi(strheight);

                    g_pHyprmagnifier->m_vSize.x = width;
                    g_pHyprmagnifier->m_vSize.y = height;

                } catch (const std::invalid_argument& e) {
                    Debug::log(NONE, "Wrong size format: \"%s\". Must be: WIDTHxHEIGHT", optarg);
                    Debug::log(NONE, "WIDTH and HEIGHT must be positive numbers", optarg);
                    exit(1);
                }
                break;
            }
            case 'h': help(); exit(0);
            case 'r': g_pHyprmagnifier->m_bRenderInactive = true; break;
            case 't': g_pHyprmagnifier->m_bNoFractional = true; break;
            case 'q': Debug::quiet = true; break;
            case 'v': Debug::verbose = true; break;
            case 'd': g_pHyprmagnifier->m_bDisableHexPreview = true; break;
            case 'l': g_pHyprmagnifier->m_bUseLowerCase = true; break;
            case 'V': {
                std::cout << "hyprmagnifier v" << HYPRMAGNIFIER_VERSION << "\n";
                exit(0);
            }

            default: help(); exit(1);
        }
    }

    g_pHyprmagnifier->init();

    return 0;
}
