/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-25     dongy       the first version
 */

#include <rt_ai_network_model.h>
#include <rt_ai.h>
#include <rt_ai_log.h>

static rt_ai_t model = NULL;
#define MNIST_0_7 {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.34058376931019385, 0.5534434156016326, 0.5159157133469962, 0.47675838274876575, 0.16790986331319932, 0.06389560571085397, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.9001142474626551, 0.7598628516908901, 0.8241672401895409, 0.8019644319085198, 0.7108184213592105, 0.4277455826754391, 0.3146021401174672, 0.2991960804831432, 0.35451095188003034, 0.35818466685703043, 0.34876617933839493, 0.3362681728806376, 0.3496743610673831, 0.3351779954733201, 0.37058414837972664, 0.2825753120721564, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.27165610171170224, 0.3410408074518168, 0.23362220981750767, 0.35993679227390263, 0.45615512866752483, 0.40289729156566256, 0.40358052318099324, 0.33999554600357185, 0.4547766756440793, 0.45948942111962493, 0.44740711894925406, 0.4245810263644414, 0.4044213569920744, 0.4299758123748652, 0.553696315814415, 0.7607796863481134, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.030172924919014375, 0.10486738003915572, 0.021155278418000027, 0.11996077664627289, 0.12120390242131839, 0.11801683846299221, 0.10020112222200817, 0.03708667465866184, 0.39950508551365427, 0.553696315814415, 0.5760189053778574, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.1465806665080444, 0.42828299421590904, 0.45560051183154626, 0.0978145311019003, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.03736313032007084, 0.4114854854984861, 0.4316686305338214, 0.1809322606795136, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.21908380960405174, 0.44857216015714796, 0.4028907218315666, 0.09591589722769395, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.10392527566144091, 0.4228827022589836, 0.44857216015714796, 0.10495472585528207, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.23427223157579052, 0.43137432278627247, 0.33024800767475065, 0.008464090794780811, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.01628112122077411, 0.3610962967897523, 0.42118437815352583, 0.1024298633429708, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.22793569709083755, 0.44740711894925406, 0.30909498719331335, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.13428445146970847, 0.4540623807127002, 0.4227468840465393, 0.09680447401109264, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.02871073499585718, 0.3956915169974076, 0.45948942111962493, 0.2923999281321897, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.004766699092688897, 0.3067515370610004, 0.4547766756440793, 0.39617394970550335, 0.06165058725678698, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.06037818850739269, 0.38381719415514337, 0.4547766756440793, 0.1392940371110674, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.05502121602879092, 0.35591353225410427, 0.38381719415514337, 0.2059028255868863, 0.0018090134689749012, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.2360587655428772, 0.40358052318099324, 0.38381719415514337, 0.0931038863523312, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.17070836103508596, 0.42952046061185173, 0.40358052318099324, 0.38381719415514337, 0.0931038863523312, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.3386182243482853, 0.45081899584880303, 0.40358052318099324, 0.33092899811014326, 0.07161837411717785, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.3386182243482853, 0.45081899584880303, 0.32890223739553387, 0.02719964368028575, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}
#define MNIST_1_2 {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.139981203251148, 0.16164718132365355, 0.23083881901548683, 0.33419760553662214, 0.32214770021188455, 0.18617473117035702, 0.1300160248725975, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.22170613428381403, 0.30530383122879695, 0.3271738949990748, 0.3415334573737905, 0.3315764478461389, 0.31962105158277176, 0.3140147132406688, 0.30476874647555113, 0.07684304219108379, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.27126840724164125, 0.33190326611718907, 0.30530383122879695, 0.3271738949990748, 0.2875360728087643, 0.1861021960243151, 0.22234507936192816, 0.3140147132406688, 0.35369950852437815, 0.3124950382437407, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.5596576869073963, 0.40128462609710247, 0.33190326611718907, 0.25341424726500933, 0.04138167841885531, 0.016199215369507847, 0.0, 0.00757994588733846, 0.25567996414062366, 0.35369950852437815, 0.358600863558391, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.8287238825359522, 0.4028897646014909, 0.27549282958343757, 0.030168362769643967, 0.0, 0.0, 0.0, 0.15412556637588204, 0.30780888886832364, 0.35369950852437815, 0.16649325808068152, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.04975929363604071, 0.02361367110715179, 0.0, 0.0, 0.0, 0.0, 0.2640347817422897, 0.3140147132406688, 0.35369950852437815, 0.16649325808068152, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.1533377248932737, 0.3120411056954333, 0.3140147132406688, 0.27680831101907855, 0.025614347397027927, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.1025950306735497, 0.3237129747746889, 0.31962105158277176, 0.2867090860023498, 0.08807537168788863, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.17279163060808372, 0.3315764478461389, 0.31962105158277176, 0.17872774192354274, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.2275992313037042, 0.33208391507491086, 0.3315764478461389, 0.2008685660144692, 0.014893978493628562, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.030168362769643967, 0.3026035234378795, 0.3415334573737905, 0.30536487094130577, 0.04421635100947435, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.23893343313558021, 0.3271738949990748, 0.3415334573737905, 0.18479161717907344, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.1023259081309911, 0.29927015867486817, 0.3271738949990748, 0.2551376420697486, 0.015726946142899868, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.03049763158337979, 0.2623741234127977, 0.30530383122879695, 0.3271738949990748, 0.19034078059171722, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.21508855958804693, 0.33190326611718907, 0.30530383122879695, 0.22371969895193652, 0.016199215369507847, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.3980743490883257, 0.33190326611718907, 0.30530383122879695, 0.03232943626473071, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.3980743490883257, 0.33190326611718907, 0.30530383122879695, 0.05560663037533683, 0.02699869228251308, 0.02621157690483311, 0.025266486291128203, 0.024823297489380936, 0.006990108864118145, 0.0, 0.015305556708432486, 0.05278772376306791, 0.055881838719442585, 0.1040759829818938, 0.39054290393292496, 0.44219130897441966, 0.4738727469974541, 0.46647395835134503, 0.07356521670154353, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.3980743490883257, 0.33190326611718907, 0.30530383122879695, 0.3271738949990748, 0.3415334573737905, 0.3315764478461389, 0.31962105158277176, 0.3140147132406688, 0.2348676578343697, 0.36628516777749937, 0.5081444827199586, 0.6677647056028091, 0.7069052598009488, 0.7116546944437603, 0.6587156979668668, 0.7458293411368544, 0.7992653666023726, 0.8028429351217027, 0.9048521654289854, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.2792940997635833, 0.33190326611718907, 0.30530383122879695, 0.3271738949990748, 0.3415334573737905, 0.3315764478461389, 0.31962105158277176, 0.3140147132406688, 0.35369950852437815, 0.6480429891448066, 0.7744611694466839, 0.6677647056028091, 0.6957288920570602, 0.694777508014264, 0.6430939818095498, 0.49820220811117943, 0.3696207426580142, 0.37127519134086645, 0.4193217351987981, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.15480073281355064, 0.14842834482664832, 0.1590608264224751, 0.16604195753745543, 0.21755608831011483, 0.31962105158277176, 0.3140147132406688, 0.35369950852437815, 0.39702238465393286, 0.3765166950274392, 0.32464450114286764, 0.1145577693748573, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}
RT_UNUSED static const float input_data0[] = MNIST_0_7;
RT_UNUSED static const float input_data1[] = MNIST_1_2;

int ai_run_complete_flag = 0;
void ai_run_complete(void *arg){
    *(int*)arg = 1;
}

int mnist_app(void){
    rt_err_t result = RT_EOK;
    int prediction = 0;
    rt_ai_buffer_t *work_buffer = rt_malloc(RT_AI_NETWORK_WORK_BUFFER_BYTES+RT_AI_NETWORK_IN_TOTAL_SIZE_BYTES+RT_AI_NETWORK_OUT_TOTAL_SIZE_BYTES);

    // find a registered model handle
    model = rt_ai_find(RT_AI_NETWORK_MODEL_NAME);
    if(!model) {rt_kprintf("ai model find err\r\n"); return -1;}


    // init the model and allocate memory
    result = rt_ai_init(model , work_buffer);
    if (result != 0) {rt_kprintf("ai init err\r\n"); return -1;}

    //prepare input data
    rt_memcpy(model->input[0], input_data0, RT_AI_NETWORK_IN_1_SIZE_BYTES);
    result = rt_ai_run(model, ai_run_complete, &ai_run_complete_flag);
    if (result != 0) {rt_kprintf("ai model run err\r\n"); return -1;}

    // get output and post-process the output
    if(ai_run_complete_flag){
        //get inferance data
        float *out = (float *)rt_ai_output(model, 0);
        //get argmax
        for(int i = 0 ; i < 10 ; i++){
            if(out[i] > out[prediction]){
                prediction = i;
            }
        }
        AI_LOG("The Mnist prediction is : %d\n", prediction);
    }
    rt_free(work_buffer);
    return 0;
}
MSH_CMD_EXPORT(mnist_app, mnist demo);


