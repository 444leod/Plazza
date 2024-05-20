/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Reception
*/

#include "Reception.hpp"
#include "IPizzaFactory.hpp"
#include "macros.hpp"

#include <iostream>

plz::Reception::Reception(plz::Setup& setup, plz::IPizzaFactory& factory) : _pizzaiolos(setup.pizzaiolos()), _restock(setup.restock()), _factory(factory)
{
}

bool plz::Reception::_queuePizza(std::map<std::shared_ptr<plz::Kitchen>, std::pair<uint32_t, uint32_t>> kitchensStatus, std::shared_ptr<plz::IPizza> pizza)
{
    for (auto& kitchen : _kitchens) {
        if (kitchensStatus[kitchen].first == kitchen->pizzaiolos() && kitchensStatus[kitchen].second == kitchen->restock()) {
            kitchen->queuePizza(pizza);
            kitchensStatus[kitchen].first--;
            kitchensStatus[kitchen].second--;
            return true;
        }
    }
    for (auto& kitchen : _kitchens) {
        if (kitchensStatus[kitchen].first > 0) {
            kitchen->queuePizza(pizza);
            kitchensStatus[kitchen].first--;
            return true;
        }
    }
    for (auto& kitchen : _kitchens) {
        if (kitchensStatus[kitchen].second > 0) {
            kitchen->queuePizza(pizza);
            kitchensStatus[kitchen].second--;
            return true;
        }
    }
    return false;
}

void plz::Reception::_spreadPizzas(std::map<std::shared_ptr<plz::Kitchen>, std::pair<uint32_t, uint32_t>> kitchensStatus)
{
    for (auto& pizza : _pizzas) {
        if (!_queuePizza(kitchensStatus, pizza))
            _addKitchen()->queuePizza(pizza);
    }
    _pizzas.clear();
}

void plz::Reception::handleCommand(UNUSED std::string command)
{
    _factory.tryCreateIPizzas(command, _pizzas);
    std::map<std::shared_ptr<plz::Kitchen>, std::pair<uint32_t, uint32_t>> kitchensStatus;
    _spreadPizzas(kitchensStatus);

    for (auto& kitchen : _kitchens) {
        kitchensStatus[kitchen] = std::make_pair(kitchen->nbOfAvailablePizzaiolos(), kitchen->nbOfAvailableStorage());
    }
}

void plz::Reception::displayKitchenStatus()
{
    uint32_t nbOfAvailablePizzaiolos = 0;
    uint32_t nbOfAvailableStorage = 0;
    plz::Ingredients ingredients;

    std::printf("[0m                                                                          [0m\n");
    std::printf("                    [38;2;188;178;164m▂[38;2;237;214;190m▂[38;2;239;215;192m▃[38;2;244;216;191m▃[38;2;218;196;174m▄[38;2;224;199;178m▄[38;2;246;221;197m▃[38;2;249;225;203m▃[38;2;231;213;195m▃[38;2;240;227;211m▂[38;2;239;225;209m▁[0m                                [0m\n");
    std::printf("               [38;2;223;195;171m▂[38;2;222;187;158m▄[38;2;204;143;107m▅[38;2;148;88;66;48;2;197;156;128m▃[38;2;217;133;82;48;2;243;191;152m▄[38;2;220;133;76;48;2;245;199;160m▄[38;2;228;141;68;48;2;245;196;159m▄[38;2;211;110;51;48;2;245;195;153m▅[38;2;225;125;47;48;2;243;195;153m▄[38;2;208;126;62;48;2;237;184;139m▅[38;2;196;119;63;48;2;224;153;98m┳[38;2;211;129;65;48;2;238;183;132m▄[38;2;216;118;50;48;2;240;182;133m▄[38;2;226;140;66;48;2;243;197;154m▄[38;2;233;147;62;48;2;246;211;171m▄[38;2;234;157;88;48;2;248;217;181m▄[38;2;240;186;137;48;2;243;222;201m▃[0m[38;2;223;196;174m▇[38;2;238;221;204m▅[38;2;227;205;184m▄[38;2;211;192;174m▂[0m                           [0m\n");
    std::printf("            [38;2;190;155;129m▃[38;2;234;193;160m▅[38;2;243;200;166;48;2;223;174;135m▝[38;2;224;155;101;48;2;244;206;172m▅[38;2;199;111;57;48;2;229;159;111m▃[38;2;223;122;58;48;2;204;127;78m▃[38;2;167;75;31;48;2;180;99;58m▅[38;2;176;77;40;48;2;216;115;50m▄[38;2;159;68;38;48;2;193;113;72m╱[38;2;208;147;114;48;2;152;77;40m▃[38;2;204;145;87;48;2;173;86;41m▂[38;2;170;162;21;48;2;154;76;25m▂[38;2;170;171;17;48;2;141;58;19m▃[38;2;216;135;69;48;2;168;66;26m▄[38;2;200;97;70;48;2;123;41;17m▅[38;2;206;167;137;48;2;130;57;35m▁[38;2;199;152;104;48;2;132;70;40m▗[38;2;151;74;37;48;2;184;109;58m╍[38;2;149;65;33;48;2;229;142;63m▃[38;2;190;106;53;48;2;231;155;82m▄[38;2;185;97;43;48;2;230;165;98m▃[38;2;224;146;78;48;2;240;189;147m▅[38;2;223;149;87;48;2;240;213;193m▆[38;2;221;163;117;48;2;235;207;185m▖[38;2;194;171;153;48;2;235;205;184m▝[0m[38;2;221;193;173m▅[38;2;180;164;153m▃[0m                        [0m\n");
    std::printf("          [38;2;209;184;162m▄[38;2;187;146;107;48;2;240;201;172m▚[38;2;210;133;86;48;2;242;192;150m▅[38;2;201;110;63;48;2;239;182;133m▄[38;2;227;155;93;48;2;206;129;71m▌[38;2;149;70;43;48;2;211;130;63m▅[38;2;147;67;47;48;2;198;114;53m▅[38;2;156;68;44;48;2;169;86;38m▅[38;2;231;173;144;48;2;169;85;47m▁[38;2;209;130;76;48;2;229;180;142m▘[38;2;219;144;110;48;2;236;197;169m▗[38;2;148;170;37;48;2;198;137;92m▗[38;2;156;162;23;48;2;185;160;69m▇[38;2;150;101;50;48;2;177;184;27m▄[38;2;213;173;136;48;2;163;133;34m▄[38;2;222;183;130;48;2;193;131;56m▇[38;2;230;212;172;48;2;196;131;92m▇[38;2;207;180;127;48;2;224;207;168m╺[38;2;110;82;57;48;2;214;194;153m▘[38;2;228;212;174;48;2;191;134;89m▋[38;2;220;148;100;48;2;160;84;53m┳[38;2;191;127;76;48;2;144;91;54m▆[38;2;214;136;81;48;2;159;76;43m▖[38;2;173;81;41;48;2;123;53;28m▆[38;2;107;43;18;48;2;176;97;59m━[38;2;154;66;29;48;2;210;143;88m▅[38;2;177;102;57;48;2;219;172;140m▅[38;2;203;134;89;48;2;232;184;148m▄[38;2;228;178;131;48;2;233;190;156m▃[38;2;232;186;153;48;2;176;157;145m▅[0m[38;2;205;176;155m▄[0m                      [0m\n");
    std::printf("        [38;2;173;137;112m▄[38;2;233;186;149;48;2;170;144;130m▆[38;2;234;176;130;48;2;237;193;163m▄[38;2;221;155;96;48;2;233;182;146m▆[38;2;178;101;61;48;2;208;132;85m┲[38;2;214;150;111;48;2;184;108;67m▃[38;2;230;180;140;48;2;207;123;74m▄[38;2;235;194;166;48;2;165;81;54m▆[38;2;245;227;201;48;2;231;168;126m▄[38;2;241;232;206;48;2;229;192;152m▗[38;2;238;233;206;48;2;239;226;191m╸[38;2;238;219;178;48;2;226;176;138m▍[38;2;225;184;155;48;2;225;215;182m▎[38;2;145;172;34;48;2;164;176;24m▌[38;2;225;181;124;48;2;163;118;48m▃[38;2;240;226;214;48;2;217;161;107m▂[38;2;221;161;92;48;2;235;204;162m▁[38;2;242;241;214;48;2;241;225;180m▗[38;2;243;228;192;48;2;234;192;143m▄[38;2;242;236;220;48;2;235;205;165m▄[38;2;206;155;123;48;2;228;210;184m╺[38;2;124;74;50;48;2;194;161;126m━[38;2;218;160;96;48;2;122;95;72m╺[38;2;214;148;102;48;2;101;82;74m╸[38;2;136;109;89;48;2;224;182;144m▍[38;2;222;162;119;48;2;207;122;92m▋[38;2;219;164;152;48;2;196;103;91m─[38;2;227;160;148;48;2;199;123;92m▄[38;2;228;169;135;48;2;164;74;44m▅[38;2;231;180;147;48;2;152;71;39m▃[38;2;155;78;44;48;2;198;131;83m▅[38;2;193;107;50;48;2;225;162;112m▃[38;2;233;174;121;48;2;242;194;152m▌[38;2;236;183;137;48;2;190;163;142m▅[0m[38;2;184;150;125m▄[0m                    [0m\n");
    std::printf("       [7m[38;2;216;173;143m▘[0m[38;2;225;167;123;48;2;233;180;139m▚[38;2;228;147;77;48;2;233;168;118m▗[38;2;216;122;53;48;2;239;174;106m▃[38;2;177;95;56;48;2;229;160;100m▅[38;2;239;186;157;48;2;221;147;122m━[38;2;199;60;47;48;2;233;183;156m▆[38;2;166;30;11;48;2;200;66;45m┏[38;2;235;199;153;48;2;210;76;62m▂[38;2;235;216;179;48;2;210;79;56m▂[38;2;216;66;32;48;2;235;195;159m▘[38;2;232;218;191;48;2;158;142;120m▊[38;2;63;53;57;48;2;209;197;169m▂[38;2;136;113;78;48;2;213;200;145m▄[38;2;127;96;39;48;2;151;167;42m▃[38;2;87;75;52;48;2;188;176;139m▆[38;2;215;188;126;48;2;101;91;79m▄[38;2;230;210;163;48;2;186;143;102m▃[38;2;236;225;184;48;2;230;186;144m▃[38;2;208;134;90;48;2;230;193;153m▗[38;2;175;130;55;48;2;228;205;165m▅[38;2;187;201;71;48;2;226;223;159m▆[38;2;192;167;36;48;2;220;197;118m▖[38;2;237;187;138;48;2;191;148;106m▃[38;2;176;143;110;48;2;225;202;158m▘[38;2;227;212;176;48;2;236;235;205m▚[38;2;172;154;129;48;2;231;214;182m▁[38;2;230;220;177;48;2;190;78;56m▄[38;2;211;188;146;48;2;187;78;61m▂[38;2;143;69;54;48;2;205;80;75m▃[38;2;188;53;47;48;2;220;142;110m▄[38;2;234;166;119;48;2;210;113;75m┳[38;2;219;137;79;48;2;184;84;31m▄[38;2;149;57;23;48;2;214;136;69m▃[38;2;203;119;69;48;2;235;172;119m▖[38;2;232;168;114;48;2;234;176;129m▚[0m[7m[38;2;220;175;142m▝[0m                   [0m\n");
    std::printf("      [38;2;168;130;104;48;2;233;184;154m▚[38;2;229;160;107;48;2;239;191;154m▄[38;2;202;129;77;48;2;229;163;109m▗[38;2;214;123;69;48;2;186;92;47m▚[38;2;237;161;103;48;2;180;92;52m▃[38;2;228;131;100;48;2;228;151;92m▗[38;2;219;98;81;48;2;200;52;39m▚[38;2;195;44;48;48;2;210;66;62m╱[38;2;226;93;68;48;2;199;73;56m▅[38;2;211;122;93;48;2;235;215;183m▅[38;2;170;99;89;48;2;240;227;199m▂[38;2;205;61;36;48;2;241;209;151m▄[38;2;219;169;121;48;2;94;70;62m▍[38;2;220;188;158;48;2;165;145;122m━[38;2;158;143;126;48;2;74;57;45m▍[38;2;223;194;144;48;2;183;130;80m▅[38;2;233;194;141;48;2;116;86;62m▅[38;2;208;98;60;48;2;223;181;135m▂[38;2;207;156;124;48;2;123;99;78m▊[38;2;128;101;77;48;2;211;191;151m▍[38;2;229;206;159;48;2;174;102;58m▋[38;2;169;151;44;48;2;185;204;66m▍[38;2;167;92;21;48;2;186;155;47m┏[38;2;242;193;146;48;2;226;138;73m▝[38;2;245;192;159;48;2;224;122;85m┗[38;2;198;121;82;48;2;226;172;135m╲[38;2;236;224;197;48;2;191;165;142m▘[38;2;142;119;98;48;2;217;202;165m▎[38;2;222;200;141;48;2;229;219;176m▗[38;2;143;129;98;48;2;76;60;49m▎[38;2;115;91;59;48;2;58;40;31m▃[38;2;211;185;158;48;2;116;64;48m▗[38;2;189;36;25;48;2;204;90;71m▚[38;2;221;152;108;48;2;203;114;61m▇[38;2;207;122;84;48;2;137;48;29m▍[38;2;184;97;48;48;2;202;128;71m▋[38;2;216;142;82;48;2;224;157;106m▖[38;2;226;154;98;48;2;232;170;126m▁[38;2;226;181;147;48;2;165;124;98m▚[0m                  [0m\n");
    std::printf("     [7m[38;2;212;153;115m▘[0m[38;2;235;165;112;48;2;204;123;73m▅[38;2;138;95;68;48;2;194;127;75m▂[38;2;97;60;41;48;2;199;139;88m▄[38;2;90;64;52;48;2;227;165;99m▅[38;2;128;99;60;48;2;226;175;118m▅[38;2;194;55;43;48;2;229;148;125m▆[38;2;167;47;33;48;2;219;44;22m▄[38;2;142;14;16;48;2;220;27;23m▅[38;2;142;17;13;48;2;219;30;30m▄[38;2;154;30;17;48;2;207;43;40m▃[38;2;219;163;131;48;2;160;98;79m┲[38;2;236;200;160;48;2;193;91;72m╾[38;2;213;93;78;48;2;195;52;32m▂[38;2;233;134;87;48;2;188;73;58m▁[38;2;219;52;22;48;2;209;138;104m▄[38;2;218;97;72;48;2;244;206;164m▅[38;2;224;137;103;48;2;199;80;50m▘[38;2;210;115;85;48;2;231;172;138m▅[38;2;226;189;174;48;2;192;133;122m▗[38;2;202;126;104;48;2;225;195;164m▆[38;2;192;94;66;48;2;205;145;97m▇[38;2;116;50;10;48;2;166;127;29m━[38;2;190;176;67;48;2;156;79;10m▃[38;2;207;81;30;48;2;214;110;48m╋[38;2;209;89;42;48;2;230;157;117m▘[38;2;237;204;179;48;2;228;172;145m▆[38;2;223;163;142;48;2;196;116;91m▌[38;2;225;180;136;48;2;184;132;106m▝[38;2;219;189;168;48;2;216;151;88m▃[38;2;199;153;109;48;2;122;80;45m▆[38;2;204;159;101;48;2;103;82;64m━[38;2;139;80;63;48;2;210;176;134m▃[38;2;204;96;69;48;2;184;39;26m▚[38;2;203;114;64;48;2;215;130;95m┺[38;2;220;140;92;48;2;186;97;59m╲[38;2;156;50;19;48;2;177;74;38m╾[38;2;171;95;45;48;2;207;135;77m╼[38;2;221;171;121;48;2;197;125;71m▅[38;2;226;166;125;48;2;233;179;135m╺[38;2;226;186;157;48;2;156;119;95m▚[0m                 [0m\n");
    std::printf("    [7m[38;2;186;136;103m▍[0m[38;2;244;186;136;48;2;229;160;113m▗[38;2;245;195;145;48;2;227;166;113m▆[38;2;100;64;43;48;2;215;154;106m▝[38;2;224;160;89;48;2;80;58;47m▃[38;2;161;157;60;48;2;63;54;24m▅[38;2;120;116;27;48;2;202;183;123m▘[38;2;212;153;98;48;2;198;60;43m▃[38;2;247;218;189;48;2;231;143;98m┍[38;2;235;177;156;48;2;203;56;49m▖[38;2;225;86;65;48;2;196;57;37m▆[38;2;211;66;31;48;2;227;96;65m▚[38;2;221;71;21;48;2;219;100;88m▅[38;2;225;83;32;48;2;231;113;86m▖[38;2;233;126;100;48;2;225;107;81m▅[38;2;222;116;87;48;2;236;178;134m▖[38;2;239;219;194;48;2;228;134;79m▆[38;2;215;195;173;48;2;190;129;95m▖[38;2;59;48;53;48;2;190;116;90m▂[38;2;212;134;114;48;2;209;90;70m▎[38;2;225;106;50;48;2;225;172;141m▅[38;2;225;105;28;48;2;227;139;74m▅[38;2;231;136;90;48;2;208;87;55m▂[38;2;205;140;92;48;2;152;92;43m┺[38;2;206;190;141;48;2;162;168;40m▄[38;2;150;165;39;48;2;207;201;102m▃[38;2;197;177;76;48;2;236;209;173m▃[38;2;223;163;137;48;2;195;83;53m▚[38;2;192;124;95;48;2;81;52;41m▋[38;2;41;24;16;48;2;75;55;48m╺[38;2;95;69;54;48;2;193;149;117m▋[38;2;214;188;147;48;2;150;113;85m▅[38;2;71;62;61;48;2;167;142;111m▂[38;2;154;139;119;48;2;81;57;42m▆[38;2;236;207;149;48;2;177;116;76m▆[38;2;243;202;126;48;2;198;117;72m▃[38;2;240;194;152;48;2;215;144;99m╶[38;2;151;67;36;48;2;221;146;105m╺[38;2;194;87;45;48;2;221;141;78m▋[38;2;216;153;97;48;2;222;168;111m┙[38;2;223;174;126;48;2;230;180;137m▍[38;2;224;172;132;48;2;215;156;120m▌[0m[38;2;181;137;111m▋                [0m\n");
    std::printf("    [38;2;171;141;121;48;2;232;172;130m▏[38;2;240;175;126;48;2;243;191;140m▌[38;2;243;194;141;48;2;226;150;96m▊[38;2;184;92;61;48;2;218;130;82m▆[38;2;196;111;59;48;2;228;183;115m▘[38;2;201;193;107;48;2;156;164;43m▍[38;2;210;190;125;48;2;144;153;54m▄[38;2;129;100;35;48;2;175;177;74m▅[38;2;140;168;38;48;2;220;200;121m▖[38;2;173;146;101;48;2;234;212;170m▗[38;2;180;140;101;48;2;210;81;71m▆[38;2;231;191;146;48;2;218;94;66m▖[38;2;211;49;38;48;2;226;99;72m▂[38;2;229;118;89;48;2;228;90;45m╸[38;2;212;77;31;48;2;238;121;83m▂[38;2;237;124;89;48;2;220;98;61m╍[38;2;221;163;119;48;2;211;92;50m▝[38;2;176;103;65;48;2;102;72;60m▎[38;2;143;123;110;48;2;83;59;54m▘[38;2;99;40;36;48;2;193;87;54m▍[38;2;228;163;120;48;2;222;115;43m▗[38;2;238;199;157;48;2;218;100;36m▅[38;2;233;212;165;48;2;196;120;73m▆[38;2;83;63;47;48;2;220;202;163m▝[38;2;186;149;107;48;2;229;217;177m▘[38;2;225;201;156;48;2;164;96;56m▎[38;2;110;89;40;48;2;153;168;40m▅[38;2;118;121;47;48;2;201;193;106m▅[38;2;146;92;84;48;2;196;165;127m▅[38;2;192;81;71;48;2;185;111;93m▖[38;2;186;119;58;48;2;233;198;181m▆[38;2;162;157;42;48;2;225;169;149m▆[38;2;156;163;45;48;2;159;121;88m▆[38;2;235;227;180;48;2;172;188;67m▂[38;2;203;208;101;48;2;180;169;67m▊[38;2;167;133;35;48;2;237;223;153m▆[38;2;213;127;79;48;2;240;195;127m▁[38;2;228;163;102;48;2;203;116;65m▌[38;2;194;103;80;48;2;180;82;47m▂[38;2;211;108;57;48;2;230;158;88m▎[38;2;230;181;132;48;2;221;153;93m▝[38;2;221;161;118;48;2;226;173;132m▃[38;2;223;167;129;48;2;164;133;110m▉[0m                [0m\n");
    std::printf("   [7m[38;2;216;172;138m▊[0m[38;2;236;173;131;48;2;232;164;116m▘[38;2;241;179;131;48;2;245;201;154m▍[38;2;239;186;135;48;2;199;98;57m▊[38;2;211;126;93;48;2;158;54;30m▄[38;2;217;137;89;48;2;231;178;130m▁[38;2;230;172;130;48;2;202;162;81m▃[38;2;155;145;30;48;2;181;160;58m┒[38;2;214;172;141;48;2;192;69;57m▖[38;2;221;82;83;48;2;159;90;38m╴[38;2;144;108;37;48;2;179;201;66m▄[38;2;109;127;8;48;2;175;183;79m▂[38;2;165;194;58;48;2;226;207;139m▄[38;2;228;183;122;48;2;179;167;70m▘[38;2;71;55;39;48;2;209;95;70m▄[38;2;63;50;35;48;2;163;99;40m▄[38;2;147;158;50;48;2;144;65;13m▆[38;2;236;193;164;48;2;179;164;71m▝[38;2;198;142;92;48;2;229;185;157m▅[38;2;206;124;90;48;2;225;171;132m▝[38;2;182;82;51;48;2;223;164;132m▋[38;2;212;161;121;48;2;237;204;159m▅[38;2;214;138;114;48;2;241;210;161m▃[38;2;243;189;128;48;2;212;117;83m▘[38;2;202;89;68;48;2;215;159;117m▄[38;2;206;62;52;48;2;213;163;131m▂[38;2;192;44;40;48;2;221;164;129m▂[38;2;208;164;143;48;2;92;79;73m▅[38;2;205;91;56;48;2;80;61;55m▃[38;2;167;82;25;48;2;216;90;39m▚[38;2;203;90;33;48;2;165;145;21m▘[38;2;146;56;14;48;2;163;157;26m▗[38;2;221;120;57;48;2;124;64;9m▄[38;2;161;84;45;48;2;228;213;170m▌[38;2;154;120;86;48;2;228;220;187m▗[38;2;99;66;40;48;2;185;144;89m━[38;2;227;169;89;48;2;173;79;43m▅[38;2;214;101;64;48;2;206;100;56m┹[38;2;232;162;122;48;2;209;115;74m╲[38;2;240;191;140;48;2;188;93;55m▄[38;2;241;188;130;48;2;200;102;62m▃[38;2;189;99;55;48;2;225;155;89m▄[38;2;219;149;91;48;2;224;161;111m▖[38;2;222;159;119;48;2;213;143;101m▊[0m[38;2;165;120;90m▍               [0m\n");
    std::printf("   [7m[38;2;205;163;129m▋[0m[38;2;240;175;128;48;2;234;165;117m▄[38;2;245;181;119;48;2;242;185;130m╺[38;2;234;163;90;48;2;193;103;59m▊[38;2;197;103;84;48;2;168;72;43m▗[38;2;233;176;146;48;2;203;109;75m▝[38;2;213;81;38;48;2;236;167;125m▖[38;2;237;123;71;48;2;240;197;167m━[38;2;236;170;114;48;2;242;206;167m╾[38;2;238;193;142;48;2;173;68;64m▇[38;2;234;194;169;48;2;203;99;83m┳[38;2;221;153;135;48;2;164;54;48m▄[38;2;211;114;81;48;2;157;74;45m▃[38;2;218;182;151;48;2;117;104;47m▆[38;2;196;167;141;48;2;76;57;49m▃[38;2;172;148;112;48;2;68;48;41m▃[38;2;138;120;79;48;2;221;201;149m▘[38;2;226;212;162;48;2;138;132;32m▃[38;2;142;94;34;48;2;193;132;76m▆[38;2;96;25;10;48;2;217;76;56m▂[38;2;167;57;55;48;2;219;72;39m▃[38;2;124;36;34;48;2;208;70;51m▗[0m[7m[38;2;191;70;65m▃[38;2;190;85;70m▄[0m[38;2;114;31;32;48;2;172;39;38m▁[38;2;155;84;55;48;2;165;21;25m▁[38;2;221;156;106;48;2;146;33;22m▃[38;2;212;132;78;48;2;181;73;44m▄[38;2;193;115;71;48;2;198;74;41m▃[38;2;181;90;43;48;2;152;145;26m▋[38;2;172;188;49;48;2;160;128;37m▊[38;2;135;49;17;48;2;176;100;74m▘[38;2;100;95;82;48;2;234;172;122m▁[38;2;237;193;147;48;2;206;129;95m▄[38;2;238;190;134;48;2;195;134;95m▖[38;2;155;46;22;48;2;173;99;59m┳[38;2;173;48;15;48;2;198;97;51m━[38;2;202;69;37;48;2;222;117;74m┳[38;2;227;117;69;48;2;221;102;54m╱[38;2;233;165;106;48;2;223;139;82m▚[38;2;219;144;79;48;2;235;166;109m▆[38;2;230;147;100;48;2;211;132;80m╹[38;2;230;162;87;48;2;237;172;107m┓[38;2;236;171;123;48;2;223;157;110m▌[0m[38;2;205;148;109m▍               [0m\n");
    std::printf("   [7m[38;2;212;170;138m▊[0m[38;2;243;195;157;48;2;238;183;140m┲[38;2;245;187;134;48;2;244;197;148m▘[38;2;239;189;135;48;2;202;117;74m▌[38;2;227;151;106;48;2;239;182;150m▌[38;2;233;157;133;48;2;217;90;62m▖[38;2;227;129;106;48;2;229;103;52m▘[38;2;228;112;25;48;2;247;208;192m▇[38;2;222;125;55;48;2;233;194;180m▅[38;2;234;175;160;48;2;187;75;55m▘[38;2;183;49;24;48;2;221;93;38m▋[38;2;237;138;65;48;2;217;73;32m▄[38;2;154;104;25;48;2;208;108;63m╺[38;2;154;138;41;48;2;206;104;44m▆[38;2;191;125;40;48;2;220;159;113m▋[38;2;243;215;186;48;2;221;174;129m▂[38;2;242;228;195;48;2;232;200;144m▅[38;2;208;71;30;48;2;208;162;125m▃[38;2;158;84;43;48;2;182;156;127m▄[38;2;195;161;113;48;2;118;96;70m▆[38;2;206;165;111;48;2;169;121;76m▄[38;2;84;74;65;48;2;217;171;120m▁[0m[38;2;203;149;122m▖[0m  [7m[38;2;129;91;62m▆[38;2;189;149;99m▄[38;2;208;169;125m▃[38;2;222;191;157m▂[0m[38;2;236;215;189;48;2;166;110;76m━[38;2;172;131;106;48;2;97;65;35m▆[38;2;69;59;53;48;2;147;127;98m▍[38;2;211;167;122;48;2;140;129;113m▇[38;2;177;108;62;48;2;212;175;142m▂[38;2;182;152;135;48;2;114;90;75m━[38;2;177;136;115;48;2;119;104;83m━[38;2;210;172;135;48;2;128;114;62m▝[38;2;150;130;32;48;2;209;158;102m▄[38;2;153;148;49;48;2;236;190;135m▅[38;2;165;167;58;48;2;226;191;148m▄[38;2;149;168;46;48;2;206;180;118m━[38;2;229;195;138;48;2;192;132;85m▅[38;2;244;192;129;48;2;225;170;116m▎[38;2;222;164;126;48;2;233;175;136m▆[0m[38;2;162;128;105m▍               [0m\n");
    std::printf("    [38;2;236;190;154;48;2;217;170;135m╋[38;2;242;181;120;48;2;243;188;143m▗[38;2;244;203;148;48;2;233;158;102m▘[38;2;209;114;62;48;2;232;166;116m▃[38;2;245;216;183;48;2;230;155;110m▘[38;2;194;49;31;48;2;216;79;44m┓[38;2;225;125;91;48;2;224;93;36m┏[38;2;201;102;57;48;2;82;44;36m▌[38;2;115;61;47;48;2;65;41;38m▝[38;2;70;42;37;48;2;126;67;43m▉[38;2;214;153;73;48;2;210;112;47m▚[38;2;204;93;35;48;2;219;142;63m╲[38;2;195;90;51;48;2;236;187;145m▆[38;2;229;212;177;48;2;204;87;53m▂[38;2;207;104;80;48;2;231;217;164m▘[38;2;198;215;87;48;2;231;216;173m▂[38;2;166;196;40;48;2;214;178;113m▃[38;2;145;160;38;48;2;205;174;51m▅[38;2;217;200;157;48;2;176;159;57m▅[38;2;184;134;116;48;2;96;70;62m▌[38;2;191;180;157;48;2;96;77;63m▆[38;2;194;144;101;48;2;213;187;156m╶[0m[38;2;208;191;159m▄[0m [7m[38;2;157;65;58m▖[0m[38;2;229;181;150;48;2;110;31;35m▄[0m[38;2;232;209;181m▄[38;2;217;207;197m▂[0m [7m[38;2;106;54;26m▇[38;2;182;131;84m▆[38;2;184;151;102m▄[0m[38;2;87;83;17;48;2;174;148;79m▄[38;2;113;68;20;48;2;162;158;63m▂[38;2;207;178;147;48;2;143;122;45m▅[38;2;231;205;180;48;2;159;108;60m▇[38;2;242;226;202;48;2;229;192;158m━[38;2;227;189;151;48;2;218;161;112m▋[38;2;219;148;90;48;2;236;196;136m▆[38;2;202;123;75;48;2;244;203;156m▆[38;2;193;121;73;48;2;230;179;132m┛[38;2;228;160;114;48;2;236;184;139m▄[38;2;220;152;117;48;2;207;158;127m▖[0m                [0m\n");
    std::printf("    [38;2;235;185;148m▝[38;2;247;194;146;48;2;233;165;107m▂[38;2;205;116;52;48;2;242;182;112m▝[38;2;244;177;100;48;2;185;84;39m▖[38;2;226;155;131;48;2;161;60;40m▝[38;2;164;63;36;48;2;212;121;98m▂[38;2;202;22;28;48;2;220;100;73m▖[38;2;228;179;132;48;2;186;85;69m▅[38;2;136;108;91;48;2;187;161;135m▆[38;2;210;179;126;48;2;175;102;73m▅[38;2;191;160;119;48;2;164;134;59m▖[38;2;109;95;44;48;2;178;205;52m▄[38;2;88;78;24;48;2;185;210;69m▃[38;2;130;61;9;48;2;178;208;62m▃[38;2;114;78;26;48;2;157;194;33m▃[38;2;200;194;135;48;2;129;157;26m▂[38;2;224;222;185;48;2;109;119;33m▄[38;2;156;137;110;48;2;229;213;178m▘[38;2;231;211;174;48;2;217;138;83m▘[38;2;241;169;119;48;2;213;101;53m▃[38;2;219;176;144;48;2;208;98;57m▝[38;2;186;188;75;48;2;221;214;162m▅[38;2;152;172;39;48;2;205;200;155m▅[0m[38;2;135;159;16m▂[0m [7m[38;2;190;147;107m▖[0m[38;2;197;83;58;48;2;237;185;150m▗[38;2;218;101;65;48;2;242;207;188m▅[38;2;221;92;47;48;2;240;211;199m▄[38;2;212;80;37;48;2;194;174;163m▃[0m[38;2;221;172;148m▆[38;2;221;192;148m▅[38;2;227;202;146m▃[38;2;137;120;85m▁[7m[38;2;124;71;44m▆[38;2;209;124;83m▆[38;2;207;134;105m▅[38;2;173;98;73m▃[0m[38;2;173;87;65;48;2;120;43;25m▘[38;2;155;70;33;48;2;225;174;126m▋[38;2;240;203;164;48;2;234;181;132m▋[38;2;230;162;119;48;2;218;152;109m▎[0m[38;2;171;125;101m▋                [0m\n");
    std::printf("     [7m[38;2;232;181;144m▖[0m[38;2;236;170;117;48;2;244;183;127m▄[38;2;248;197;122;48;2;243;171;83m▘[38;2;243;175;114;48;2;202;98;54m▖[38;2;146;59;39;48;2;180;86;59m▝[38;2;195;101;71;48;2;185;37;30m▖[38;2;234;182;148;48;2;213;76;48m▝[38;2;229;187;144;48;2;170;138;106m▇[38;2;239;216;172;48;2;215;186;132m▃[38;2;229;204;162;48;2;183;136;100m▆[38;2;162;125;98;48;2;78;51;40m▆[38;2;65;51;50;48;2;43;27;29m▂[38;2;109;51;45;48;2;180;53;36m▎[38;2;221;142;98;48;2;205;59;23m▝[38;2;234;203;163;48;2;227;168;114m▚[38;2;213;170;112;48;2;230;205;165m╼[38;2;175;77;40;48;2;208;129;73m▖[38;2;233;136;64;48;2;224;115;23m┗[38;2;248;209;167;48;2;242;166;97m▗[38;2;224;117;69;48;2;226;96;45m▏[38;2;215;104;68;48;2;233;210;173m▍[38;2;217;196;135;48;2;121;107;37m▅[38;2;212;176;109;48;2;153;152;28m▂[38;2;161;174;25;48;2;108;125;10m▎[0m [7m[38;2;197;147;105m▖[0m[38;2;219;120;45;48;2;201;44;11m▆[38;2;237;140;50;48;2;209;51;24m▆[38;2;237;112;11;48;2;221;82;37m▄[38;2;236;124;25;48;2;214;81;33m▄[38;2;211;80;25;48;2;206;120;99m▆[38;2;201;92;66;48;2;241;213;166m▅[38;2;240;219;164;48;2;214;169;94m▚[38;2;238;222;181;48;2;185;184;51m▃[0m[38;2;202;157;106m▆[38;2;199;129;71m▄[38;2;176;71;60m▃[38;2;180;106;82m▂[0m [7m[38;2;132;79;47m▆[38;2;177;121;95m▅[0m                 [0m\n");
    std::printf("      [7m[38;2;234;167;120m▖[0m[38;2;238;161;98;48;2;240;176;123m▂[38;2;238;175;119;48;2;227;132;75m▅[38;2;224;150;102;48;2;191;99;68m▆[38;2;230;160;108;48;2;204;118;73m╲[38;2;227;181;136;48;2;186;45;28m▄[38;2;210;140;98;48;2;208;56;31m▂[38;2;172;29;24;48;2;239;189;155m▅[38;2;150;34;28;48;2;237;168;136m▅[38;2;162;66;49;48;2;211;160;118m▋[38;2;235;210;164;48;2;164;112;83m▄[38;2;234;204;158;48;2;170;110;81m▆[38;2;233;196;141;48;2;184;69;53m▅[38;2;225;180;136;48;2;198;38;24m▄[38;2;219;118;90;48;2;204;79;53m┸[38;2;195;61;16;48;2;222;110;69m▘[38;2;207;61;38;48;2;237;125;25m▂[38;2;233;102;15;48;2;243;148;32m▅[38;2;201;75;41;48;2;220;104;57m▄[38;2;86;46;45;48;2;198;125;97m▅[38;2;111;102;84;48;2;221;205;158m▆[38;2;225;199;150;48;2;197;171;126m╲[38;2;210;189;109;48;2;152;164;34m▋[0m[38;2;142;166;19m▌[0m [7m[38;2;123;67;42m▄[0m[38;2;173;77;34;48;2;241;149;85m▋[38;2;240;150;100;48;2;237;135;60m▃[38;2;213;79;41;48;2;237;129;30m▆[38;2;201;46;22;48;2;210;69;24m▖[38;2;219;101;50;48;2;212;70;31m▝[38;2;191;65;48;48;2;211;98;70m╲[38;2;216;158;121;48;2;235;202;156m▇[38;2;216;169;127;48;2;207;127;75m▍[38;2;223;154;102;48;2;203;94;38m▅[38;2;229;155;104;48;2;201;75;57m▄[38;2;182;28;22;48;2;200;60;50m┣[38;2;186;83;56;48;2;237;163;115m▅[38;2;205;131;89;48;2;150;71;43m▚[38;2;231;158;102;48;2;153;127;98m▖[0m[38;2;222;197;173m▅[38;2;210;173;143m▃[0m               [0m\n");
    std::printf("       [7m[38;2;207;137;83m▖[0m[38;2;245;195;142;48;2;239;163;105m▝[38;2;248;203;150;48;2;245;181;118m▚[38;2;246;206;156;48;2;185;98;61m▄[38;2;247;197;124;48;2;197;115;73m▃[38;2;248;191;105;48;2;218;141;79m▁[38;2;223;173;123;48;2;160;75;47m▅[38;2;221;198;157;48;2;175;131;101m▆[38;2;162;129;89;48;2;209;182;142m╹[38;2;100;75;58;48;2;224;198;142m▃[38;2;155;119;74;48;2;223;189;127m▖[38;2;234;209;156;48;2;241;227;191m▋[38;2;234;197;171;48;2;214;103;61m▍[38;2;239;126;28;48;2;211;74;31m▅[38;2;230;84;10;48;2;223;84;66m▆[38;2;227;80;23;48;2;231;104;77m▄[38;2;233;134;76;48;2;221;104;59m━[38;2;205;157;134;48;2;195;78;50m▗[38;2;217;200;151;48;2;102;65;52m▅[38;2;154;91;74;48;2;210;181;148m▚[38;2;166;47;34;48;2;183;114;89m▇[38;2;224;192;145;48;2;190;152;73m▂[38;2;108;100;15;48;2;197;171;88m┛[0m[7m[38;2;171;146;103m▝[0m [7m[38;2;164;119;77m▋[0m[38;2;189;98;65;48;2;231;125;78m▅[38;2;199;71;35;48;2;214;85;44m▂[38;2;236;134;54;48;2;216;90;23m╅[38;2;216;79;7;48;2;199;60;20m▖[38;2;201;73;45;48;2;162;45;34m▊[38;2;146;75;65;48;2;78;50;47m▎[38;2;94;63;54;48;2;56;34;31m▅[38;2;95;71;60;48;2;204;134;78m▍[38;2;231;169;133;48;2;218;133;87m╱[38;2;193;72;39;48;2;180;33;23m▚[38;2;233;172;128;48;2;213;132;93m┻[38;2;244;192;141;48;2;208;119;69m▆[38;2;244;195;142;48;2;241;181;134m▘[38;2;226;164;124;48;2;232;178;135m▆[38;2;182;144;120;48;2;230;185;154m▚[0m[38;2;114;96;83m▘              [0m\n");
    std::printf("        [7m[38;2;182;133;101m▅[0m[38;2;242;172;117;48;2;199;136;96m▝[38;2;237;165;111;48;2;249;189;139m▅[38;2;250;208;160;48;2;244;181;122m╺[38;2;248;204;151;48;2;241;169;70m▅[38;2;199;115;66;48;2;224;170;132m━[38;2;233;208;164;48;2;221;184;135m╲[38;2;237;209;177;48;2;208;179;126m▄[38;2;153;122;83;48;2;221;181;138m▝[38;2;118;89;60;48;2;177;137;101m┗[38;2;198;160;108;48;2;232;196;160m▘[38;2;196;103;74;48;2;202;74;33m▎[38;2;216;83;23;48;2;237;116;13m▆[38;2;184;57;33;48;2;231;111;25m▃[38;2;190;65;32;48;2;205;98;54m┶[38;2;157;84;59;48;2;71;40;31m▍[38;2;126;116;101;48;2;53;41;38m▂[38;2;102;85;75;48;2;194;162;137m▘[38;2;191;54;34;48;2;215;116;83m▉[38;2;229;205;154;48;2;159;100;73m▄[38;2;130;107;84;48;2;231;206;157m▘[38;2;203;173;125;48;2;229;209;164m┎[38;2;150;97;42;48;2;190;150;97m┣[0m[38;2;152;130;85m▎[0m [7m[38;2;164;111;67m▖[0m[38;2;197;153;106;48;2;192;79;45m▅[38;2;218;176;136;48;2;192;68;30m▅[38;2;222;177;146;48;2;197;65;32m▄[38;2;203;95;81;48;2;171;55;37m┍[38;2;213;142;105;48;2;125;57;38m▆[38;2;202;119;82;48;2;122;64;29m▆[38;2;163;34;28;48;2;194;113;77m▅[38;2;209;133;93;48;2;146;35;27m▁[38;2;216;137;86;48;2;177;83;41m▂[38;2;159;92;63;48;2;184;114;78m┓[38;2;243;183;134;48;2;217;139;88m▝[38;2;229;173;138;48;2;224;158;120m▚[38;2;214;177;155;48;2;179;147;125m┗[0m[38;2;129;109;95m▘               [0m\n");
    std::printf("          [7m[38;2;184;128;92m▄[0m[38;2;167;120;91;48;2;230;158;112m▄[38;2;229;160;110;48;2;246;186;137m▆[38;2;242;186;138;48;2;247;213;176m▅[38;2;246;213;172;48;2;232;175;133m┳[38;2;243;206;170;48;2;208;131;79m▄[38;2;239;204;163;48;2;204;120;63m▂[38;2;187;109;53;48;2;217;157;115m▄[38;2;147;78;37;48;2;181;137;84m▝[38;2;160;160;58;48;2;174;59;33m▅[38;2;206;187;107;48;2;194;61;34m▆[38;2;202;191;122;48;2;193;129;94m▅[38;2;139;123;70;48;2;195;190;104m▌[38;2;190;194;87;48;2;131;140;34m▌[38;2;60;65;24;48;2;137;140;72m╼[38;2;74;40;41;48;2;150;112;91m┳[38;2;208;123;86;48;2;166;30;21m▝[38;2;210;122;95;48;2;224;186;129m▖[38;2;174;133;77;48;2;226;200;148m▂[38;2;216;206;167;48;2;189;159;102m▘[38;2;208;138;87;48;2;215;172;125m▂[38;2;213;169;134;48;2;175;121;83m┻[0m[38;2;142;104;70m▖[0m [38;2;176;147;91;48;2;83;63;38m┎[38;2;162;136;74;48;2;109;77;51m▃[38;2;231;183;140;48;2;187;125;77m╺[38;2;230;192;152;48;2;213;145;98m╸[38;2;235;179;133;48;2;174;93;55m▂[38;2;240;198;155;48;2;210;130;101m▂[38;2;250;209;160;48;2;200;118;89m▂[38;2;246;191;126;48;2;208;121;65m▄[38;2;221;138;64;48;2;243;175;109m▘[38;2;229;163;122;48;2;232;153;83m▂[38;2;209;155;126;48;2;198;116;70m▅[0m[7m[38;2;169;126;106m▃[0m                 [0m\n");
    std::printf("            [7m[38;2;161;116;88m▅[38;2;211;149;108m▃[0m[38;2;207;147;109;48;2;242;184;136m▇[38;2;223;157;116;48;2;244;186;140m▅[38;2;226;150;98;48;2;244;199;153m▄[38;2;172;88;46;48;2;222;155;101m▝[38;2;240;190;142;48;2;212;131;87m▄[38;2;182;101;47;48;2;225;191;141m━[38;2;213;160;111;48;2;158;133;54m▃[38;2;157;108;56;48;2;176;191;32m▆[38;2;188;138;97;48;2;137;134;36m▄[38;2;211;158;88;48;2;63;58;28m▅[38;2;218;178;115;48;2;88;77;64m▃[38;2;216;165;120;48;2;106;86;68m▃[38;2;198;149;105;48;2;189;111;79m▍[38;2;203;129;91;48;2;153;33;28m▅[38;2;156;91;44;48;2;175;139;38m▌[38;2;191;147;55;48;2;226;182;138m▍[38;2;247;203;154;48;2;211;138;76m▃[38;2;246;215;178;48;2;199;132;92m▅[38;2;240;221;200;48;2;209;175;134m━[0m[38;2;137;108;79m▖[38;2;44;36;17m▝[38;2;135;95;70;48;2;69;53;43m┙[38;2;82;53;42;48;2;153;81;56m▍[38;2;148;67;39;48;2;204;135;97m▆[38;2;215;143;78;48;2;238;189;141m▆[38;2;235;168;90;48;2;246;201;146m▆[38;2;233;163;99;48;2;248;207;155m▄[38;2;221;165;126;48;2;232;163;104m▂[38;2;207;154;122;48;2;224;153;106m▃[0m[7m[38;2;200;146;116m▃[0m[38;2;110;86;73m▘                  [0m\n");
    std::printf("               [7m[38;2;180;133;103m▆[38;2;199;129;83m▅[38;2;203;133;90m▃[0m[38;2;166;109;79;48;2;235;160;108m▆[38;2;203;132;95;48;2;238;174;126m▅[38;2;207;137;96;48;2;249;207;168m▆[38;2;210;137;94;48;2;243;195;147m▅[38;2;208;134;93;48;2;240;191;150m▃[38;2;224;159;114;48;2;241;185;121m▃[38;2;246;195;150;48;2;235;181;126m╼[38;2;226;159;115;48;2;242;192;141m▂[38;2;245;219;188;48;2;226;166;123m━[38;2;219;148;107;48;2;238;195;155m▃[38;2;216;150;114;48;2;244;201;153m▄[38;2;225;163;119;48;2;248;208;159m▆[38;2;221;160;122;48;2;244;194;147m▆[38;2;198;151;127;48;2;235;175;135m▄[0m[7m[38;2;218;157;118m▁[0m[38;2;217;131;74m▘ [38;2;52;19;13m▝[38;2;229;179;137;48;2;163;91;55m▗[38;2;247;218;195;48;2;230;190;156m━[38;2;240;203;162;48;2;228;173;132m▘[38;2;226;159;101;48;2;220;159;115m╹[38;2;170;125;98;48;2;223;166;126m▅[0m[7m[38;2;197;147;118m▄[38;2;95;67;51m▆[0m                    [0m\n");
    std::printf("                    [7m[38;2;166;115;86m▇[38;2;179;120;93m▆[38;2;177;122;97m▅[38;2;193;135;107m▅[38;2;205;153;128m▅[38;2;189;147;127m▄[38;2;204;151;123m▅[38;2;194;142;115m▅[38;2;182;132;107m▅[38;2;207;155;127m▆[38;2;199;153;131m▇[0m     [38;2;188;100;58m▝[7m[38;2;207;138;101m▃[38;2;195;142;114m▄[38;2;155;120;97m▆[0m                       [0m\n");
    std::printf("                                                               [0m\n");

    for (auto &kitchen : _kitchens) {
        nbOfAvailablePizzaiolos = kitchen->nbOfAvailablePizzaiolos();
        nbOfAvailableStorage = kitchen->nbOfAvailableStorage();
        ingredients = kitchen->getIngredients();

        std::printf("┌───────────────────────────────────┐\n");
        std::printf("│                                   │\n");
        std::printf("│            Pizzeria %.3d           │\n", kitchen->id());
        std::printf("│                                   │\n");
        std::printf("│      Cooking pizzas: %3d/%-3d      │\n", kitchen->pizzaiolos() - nbOfAvailablePizzaiolos, kitchen->pizzaiolos());
        std::printf("│     Storaged pizzas: %3d/%-3d      │\n", kitchen->restock() - nbOfAvailableStorage, kitchen->restock());
        std::printf("│                                   │\n");
        std::printf("│           Ingredients:            │\n");
        std::printf("│                                   │\n");
        std::printf("│ %3d dough         %3d tomato      │\n", ingredients.dough, ingredients.tomato);
        std::printf("│ %3d gruyere       %3d ham         │\n", ingredients.gruyere, ingredients.ham);
        std::printf("│ %3d mushrooms     %3d steak       │\n", ingredients.mushrooms, ingredients.steak);
        std::printf("│ %3d eggplant      %3d goatCheese  │\n", ingredients.eggplant, ingredients.goatCheese);
        std::printf("│ %3d chiefLove                     │\n", ingredients.chiefLove);
        std::printf("│                                   │\n");
        std::printf("└───────────────────────────────────┘\n");
    }
}

std::shared_ptr<plz::Kitchen> plz::Reception::_addKitchen()
{
    std::shared_ptr<plz::Kitchen> kitchen = std::make_shared<plz::Kitchen>(_pizzaiolos, _restock);

    _kitchens.push_back(kitchen);
    return kitchen;
}
