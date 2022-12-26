import re

small_input = """Sensor at x=2, y=18: closest beacon is at x=-2, y=15
Sensor at x=9, y=16: closest beacon is at x=10, y=16
Sensor at x=13, y=2: closest beacon is at x=15, y=3
Sensor at x=12, y=14: closest beacon is at x=10, y=16
Sensor at x=10, y=20: closest beacon is at x=10, y=16
Sensor at x=14, y=17: closest beacon is at x=10, y=16
Sensor at x=8, y=7: closest beacon is at x=2, y=10
Sensor at x=2, y=0: closest beacon is at x=2, y=10
Sensor at x=0, y=11: closest beacon is at x=2, y=10
Sensor at x=20, y=14: closest beacon is at x=25, y=17
Sensor at x=17, y=20: closest beacon is at x=21, y=22
Sensor at x=16, y=7: closest beacon is at x=15, y=3
Sensor at x=14, y=3: closest beacon is at x=15, y=3
Sensor at x=20, y=1: closest beacon is at x=15, y=3"""


large_input = """Sensor at x=3842919, y=126080: closest beacon is at x=3943893, y=1918172
Sensor at x=406527, y=2094318: closest beacon is at x=-1066, y=1333278
Sensor at x=2208821, y=3683408: closest beacon is at x=2914373, y=3062268
Sensor at x=39441, y=1251806: closest beacon is at x=-1066, y=1333278
Sensor at x=3093352, y=2404566: closest beacon is at x=2810772, y=2699609
Sensor at x=3645473, y=2234498: closest beacon is at x=3943893, y=1918172
Sensor at x=3645012, y=2995540: closest beacon is at x=4001806, y=2787325
Sensor at x=18039, y=3083937: closest beacon is at x=103421, y=3007511
Sensor at x=2375680, y=551123: closest beacon is at x=2761373, y=2000000
Sensor at x=776553, y=123250: closest beacon is at x=-1066, y=1333278
Sensor at x=2884996, y=2022644: closest beacon is at x=2761373, y=2000000
Sensor at x=1886537, y=2659379: closest beacon is at x=2810772, y=2699609
Sensor at x=3980015, y=3987237: closest beacon is at x=3844688, y=3570059
Sensor at x=3426483, y=3353349: closest beacon is at x=3844688, y=3570059
Sensor at x=999596, y=1165648: closest beacon is at x=-1066, y=1333278
Sensor at x=2518209, y=2287271: closest beacon is at x=2761373, y=2000000
Sensor at x=3982110, y=3262128: closest beacon is at x=3844688, y=3570059
Sensor at x=3412896, y=3999288: closest beacon is at x=3844688, y=3570059
Sensor at x=2716180, y=2798731: closest beacon is at x=2810772, y=2699609
Sensor at x=3575486, y=1273265: closest beacon is at x=3943893, y=1918172
Sensor at x=7606, y=2926795: closest beacon is at x=103421, y=3007511
Sensor at x=2719370, y=2062251: closest beacon is at x=2761373, y=2000000
Sensor at x=1603268, y=1771299: closest beacon is at x=2761373, y=2000000
Sensor at x=3999678, y=1864727: closest beacon is at x=3943893, y=1918172
Sensor at x=3157947, y=2833781: closest beacon is at x=2914373, y=3062268
Sensor at x=3904662, y=2601010: closest beacon is at x=4001806, y=2787325
Sensor at x=3846359, y=1608423: closest beacon is at x=3943893, y=1918172
Sensor at x=2831842, y=3562642: closest beacon is at x=2914373, y=3062268
Sensor at x=3157592, y=1874755: closest beacon is at x=2761373, y=2000000
Sensor at x=934300, y=2824967: closest beacon is at x=103421, y=3007511
Sensor at x=3986911, y=1907590: closest beacon is at x=3943893, y=1918172
Sensor at x=200888, y=3579976: closest beacon is at x=103421, y=3007511
Sensor at x=967209, y=3837958: closest beacon is at x=103421, y=3007511
Sensor at x=3998480, y=1972726: closest beacon is at x=3943893, y=1918172"""


def is_overlapping(pos_a, pos_b):
    return pos_a[1] >= pos_b[0]


list_of_positions_str = large_input.split("\n")

sensor_positions = []
closest_beacon_positions = []
for each_str in list_of_positions_str:
    matches = re.search(
        "Sensor at x=(.+?), y=(.+?): closest beacon is at x=(.+?), y=(.+)", each_str
    )
    sensor_positions.append([int(matches.group(1)), int(matches.group(2))])
    closest_beacon_positions.append([int(matches.group(3)), int(matches.group(4))])

for y in range(0, 4_000_000):
    row_y = y
    start_pos_on_y = []
    for id_sp, sensor_pos in enumerate(sensor_positions):
        closest_beacon_pos = closest_beacon_positions[id_sp]
        vertical_distance = abs(closest_beacon_pos[1] - sensor_pos[1])
        horizontal_distance = abs(closest_beacon_pos[0] - sensor_pos[0])
        dist_btw_sensor_and_becon = horizontal_distance + vertical_distance
        max_range_of_sensor = sensor_pos[1] + dist_btw_sensor_and_becon
        min_range_of_sensor = sensor_pos[1] - dist_btw_sensor_and_becon
        if max_range_of_sensor > row_y and min_range_of_sensor < row_y:
            # sensor_pos_on_row_y = [,row_y]
            remaining_dist = abs(dist_btw_sensor_and_becon - abs(row_y - sensor_pos[1]))
            start_pos_on_y.append(
                sorted([sensor_pos[0] + remaining_dist, sensor_pos[0] - remaining_dist])
            )

    start_pos_on_y = sorted(start_pos_on_y)
    # print([f"{id}: {i}" for id, i in enumerate(start_pos_on_y)], len(start_pos_on_y))
    j = 1
    posi = start_pos_on_y[0]
    segment_found = 0
    found = False
    while j < len(start_pos_on_y):
        posj = start_pos_on_y[j]
        if is_overlapping(posi, posj):
            posi = [posi[0], max(posi[1], posj[1])]
        else:
            found = True
            print(posj, posi, y)
            break
            segment_found += posi[1] - posi[0]
            # print(segment_found, j, posi, posj)
            posi = posj
        j += 1
    segment_found += posi[1] - posi[0]
    if found:
        print(y)
        break
    # print(segment_found)
# set_becons = set()
# for i in closest_beacon_positions:
#     if row_y == i[1]:
#         set_becons.add(f"{i[0]}__{i[1]}")
