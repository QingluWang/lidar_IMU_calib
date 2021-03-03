#!/usr/bin/env bash

bag_path="/home/cxzn/dataset/rs128"

outdoor_sync_bag_name=(
"calib.bag"
# "rs128_INS570d_2020-12-09-10-48-49.bag"
#"Court-02.bag"
#"Court-03.bag"
#"Court-04.bag"
#"Court-05.bag"
)

indoor_sync_bag_name=(
#"Garage-01.bag"
#"Garage-02.bag"
#"Garage-03.bag"
#"Garage-04.bag"
#"Garage-05.bag"
)

imu_topic_name=(
"/ins_570d_imu"
#"/imu2/data_sync"
#"/imu3/data_sync"
)

bag_start=1
bag_durr=30
scan4map=15
timeOffsetPadding=0.015
# timeOffsetPadding=3.15

show_ui=true  #false

bag_count=-1
sync_bag_name=(${outdoor_sync_bag_name[*]} ${indoor_sync_bag_name[*]})
for i in "${!sync_bag_name[@]}"; do
    let bag_count=bag_count+1

    ndtResolution=0.5	# indoor
    if [ $bag_count -lt ${#outdoor_sync_bag_name[*]} ]; then
        # wql begin
        ndtResolution=1.0 # outdoor
        # wql end
    fi

    for j in "${!imu_topic_name[@]}"; do
        path_bag="$bag_path/${sync_bag_name[i]}"

        echo "topic_imu:=${imu_topic_name[j]}"
        echo "path_bag:=${path_bag}"
        echo "ndtResolution:=${ndtResolution}"
        echo "=============="

        roslaunch li_calib licalib_gui.launch \
                          topic_imu:="${imu_topic_name[j]}" \
                          path_bag:="${path_bag}" \
                          bag_start:="${bag_start}" \
                          bag_durr:="${bag_durr}" \
                          scan4map:="${scan4map}" \
                          lidar_model:="RS_128" \
                          time_offset_padding:="${timeOffsetPadding}"\
                          ndtResolution:="${ndtResolution}" \
                          show_ui:="${show_ui}"
    done
done
