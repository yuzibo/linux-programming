#!/bin/bash

function run_gtest_target() {
    local testlist_txt=$(get_gtest_testlists_file)
    local gtest_tmp_log=$(get_gtest_tmp_log_file)
    local start_day_time=$(date "+%Y-%m-%d")
    local start_hour=$(date "+%H:%M")
    echo "#### Started run gtest at _MY_TIME_ ${start_day_time}-${start_hour} ####" 2>&1 | tee -a $gtest_tmp_log
    for line in $(cat ${testlist_txt}); do
        echo -e "\n" 2>&1 | tee -a $gtest_tmp_log
        echo "#### Started run ${line}  Started ####" 2>&1 | tee -a $gtest_tmp_log

        adb shell /data/nativetest64/${line} 2>&1 | tee -a $gtest_tmp_log

        echo "#### Finished run ${line}  Finished ####" 2>&1 | tee -a $gtest_tmp_log
    done
    local end_day_time=$(date "+%Y-%m-%d")
    local end_hour=$(date "+%H:%M")
    echo "#### End run gtest at _MY_TIME_ ${end_day_time}-${end_hour} ####" 2>&1 | tee -a $gtest_tmp_log
    # 产生中间文件
    generate_tmp_file
}

function generate_tmp_file() {
    # rm -rf summary_run_log.txt
    #### generate summary report ####
    reporting="false"
    start1="Global test environment tear-down"
    start2="Started ####"
    start3="Aborted "
    stop1="out/target/product"

    local testlist_txt=$(get_gtest_testlists_file)
    local gtest_tmp_log=$(get_gtest_tmp_log_file)
    echo "$gtest_tmp_log"

    IFS_old=$IFS # 记录老的分隔符
    IFS=$'\n'    # 以换行符作为分隔符

    for line in $(cat $gtest_tmp_log); do

        if [[ $line == *$start1* ]]; then
            reporting="true"
        fi

        if [[ $line == *$start2* ]]; then
            reporting="true"
        fi

        if [[ $line == *$stop1* ]]; then
            reporting="false"
        fi

        if [[ $reporting = "true" ]]; then
            echo ${line} 2>&1 | tee -a summary_run_log.txt
        fi
    done
}

function get_test_script_file_dir() {
    current_dir=$(
        cd "$(dirname "${BASH_SOURCE[0]}")"
        pwd
    )
    echo $current_dir
}

function get_test_python() {
    TEST_DIR=$(get_test_script_file_dir)
    echo $TEST_DIR/write_execl.py
}

function get_testlist() {
    local testlist_txt=$(get_gtest_testlists_file)
    for element in $(ls $1); do
        # dir_or_file=$1"/"$element
        if [[ $element =~ "_test" ]]; then
            echo $2"/"$element 2>&1 | tee -a $testlist_txt
        fi
    done
}

function get_target_gtest_lists() {
    local testlist_txt=$(get_gtest_testlists_file)
    for element in $(ls $1); do
        dir_or_file=$1"/"$element
        if [[ $element =~ "_tests" ]]; then
            get_testlist $dir_or_file $element
        fi
    done
    local path=0
    if [ -d "$1/art/riscv64" ]; then
        path=$1/art/riscv64
        for element in $(ls $path); do
            dir_or_file=$path"/"$element
            if [[ $element =~ "_tests" ]]; then
                get_testlist $dir_or_file art/riscv64/$element
            fi
        done
    elif [ -d "$1/art/x86_64" ]; then
        path=$1/art/x86_64
        for element in $(ls $path); do
            dir_or_file=$path"/"$element
            if [[ $element =~ "_tests" ]]; then
                get_testlist $dir_or_file art/x86_64/$element
            fi
        done
    fi
    echo "testlist txt generated!"
}

# get image arch, for example: eswin_riscv64
function get_target_arch() {
    local T=$(gettop)
    local out_temp=$OUT
    local target_arch=${out_temp##*/}
    echo $target_arch
}

function get_eswin_art_test_directory() {
    local T=$(gettop)
    local target_arch=$(get_target_arch)
    eswin_art_test_dir="$T/out/target/product/$target_arch/eswin_art_test"
    $(mkdir -p $eswin_art_test_dir)
    echo $eswin_art_test_dir
}

# Create eswin_art_test dir to save some tmp files
# Need to do for run test file, return dir is ok, not full file path
###  *_*: file name to be altered
function get_gtest_testlists_file() {
    local eswin_art_test_dir=$(get_eswin_art_test_directory)
    echo $eswin_art_test_dir/test-list.txt
}

# Not use it this time
function get_gtest_tmp_log_file() {
    local eswin_art_test_dir=$(get_eswin_art_test_directory)
    echo $eswin_art_test_dir/gtest_tmp_run_log.txt
}

function get_rtest_tmp_log_file() {
    local eswin_art_test_dir=$(get_eswin_art_test_directory)
    echo $eswin_art_test_dir/rtest_tmp_run_log.txt
}

function get_rtest_time_file() {
    local eswin_art_test_dir=$(get_eswin_art_test_directory)
    echo $eswin_art_test_dir/rtest_time.txt
}
function get_art_test_config() {
    local eswin_art_test_dir=$(get_eswin_art_test_directory)
    echo $eswin_art_test_dir/config.txt
}

function gtest_root_dir() {
    local T=$(gettop)
    local out_temp=$OUT
    local target_arch=${out_temp##*/}
    gtest_target_bin_root_dir="$T/out/target/product/$target_arch/data/nativetest64"
    # Bash function can not return string directly.
    echo $gtest_target_bin_root_dir
}

# Delete existing gtest log and libary files
function del_existing_files() {
    local testlist_txt=$(get_gtest_testlists_file)
    local gtest_tmp_log=$(get_gtest_tmp_log_file)
    local rtest_txt=$(get_rtest_tmp_log_file)
    local rtest_time=$(get_rtest_time_file)
    (
        rm $testlist_txt
        rm $gtest_tmp_log
        rm $rtest_txt
        rm /tmp/rtest_log.txt
        rm $rtest_time
    )

}

# host 端的测试
function run_gtest_host() {
    local gtest_tmp_log=$(get_gtest_tmp_log_file)
    local T=$(gettop)
    echo "debug $gtest_tmp_log"
    echo "#### Started gtest-host run art_compiler_host_tests/assembler_riscv64_test  Started ####" 2>&1 | tee -a $gtest_tmp_log
    $T/out/host/linux-x86/nativetest/art_compiler_host_tests/assembler_riscv64_test --gtest_also_run_disabled_tests 2>&1 | tee -a $gtest_tmp_log
    echo "#### Finished gtest-host run art_compiler_host_tests/assembler_riscv64_test  Finished ####" 2>&1 | tee -a $gtest_tmp_log

    echo "#### Started gtest-host run art_compiler_host_tests/emit_parallel_move_riscv64_test  Started ####" 2>&1 | tee -a $gtest_tmp_log
    $T/out/host/linux-x86/nativetest64/art_compiler_host_tests/emit_parallel_move_riscv64_test --gtest_also_run_disabled_tests 2>&1 | tee -a $gtest_tmp_log
    echo "#### Finished gtest-host run art_compiler_host_tests/emit_parallel_move_riscv64_test  Finished ####" 2>&1 | tee -a $gtest_tmp_log
    echo "run_gtest finished!!!"
}

function execute_python_file() {
    echo "start write excel"
    create_execl_file=$(get_test_python)
    python $create_execl_file
    echo "finish write excel"
}

function adb_ops() {
    adb root
    adb remount
    adb sync data
    adb sync system
}

function run_art_target_gtest_test() {

    # mm test-art-target-gtest will copy compiled file
    # located in bellow dir. It will case confusion
    # between old files and newest test cases.
    (\rm -rf out/soong/.intermediates/art/)
    echo -e "comiling gtest-target test:\n"
    (mm test-art-target-gtest)

    adb_ops
    if [[ $? != 0 ]]; then
        return
    fi

    ## Run gtest with target
    gtest_bin_root_dir=$(gtest_root_dir)
    if [[ $? != 0 ]]; then
        echo -e "why not entry in it?"
        return
    fi
    # generate all gtest exe files auto scan gtest dir
    get_target_gtest_lists $gtest_bin_root_dir
    if [[ $? != 0 ]]; then
        echo -e "get list"
        return
    fi

    run_gtest_target
}

# Why need it? After mm  test-art-target-gtest
# to run mmm art/compiler/utils/ will fail.
# So togetger them to avoid this
function compiled_art_test_target_and_host() {
    # First generate gtest target bin
    echo -e "compiling gtest host mmm art/compiler/utils/ -j32:\n"
    (mmm art/compiler/utils/ -j32)
    echo -e "compiling gtest host mmm art/compiler/optimizing/ -j12:\n"
    (mmm art/compiler/optimizing/ -j12)
    echo -e "compiling gtest host mmm libcore\n"
    (mmm libcore)

}

function run_rtest_target() {
    echo -e "make d8"
    (make d8)
    (\mm test-art-target-run-test -j32)
    adb_ops
    local rtest_txt=$(get_rtest_tmp_log_file)
    local rtest_time=$(get_rtest_time_file)

    local start_day_time=$(date "+%Y-%m-%d")
    local start_hour=$(date "+%H:%M")
    (echo "#### Started run rtest at _MY_TIME_ ${start_day_time}-${start_hour} ####" 2>&1 | tee -a $rtest_time)
    (art/test.py --target -r --speed --64 -j4 2>&1 | tee -a $rtest_txt)
    local end_day_time=$(date "+%Y-%m-%d")
    local end_hour=$(date "+%H:%M")
    echo "#### End run rtest at _MY_TIME_ ${end_day_time}-${end_hour} ####" 2>&1 | tee -a $rtest_time
}
function backup_log_file() {
    #CUR_DIR=`pwd`
    TEST_DIR=$(get_test_script_file_dir)
    echo -e "debug $TEST_DIR"
    local T=$(gettop)
    local target_arch=$(get_target_arch)
    eswin_art_test_dir="$T/out/target/product/$target_arch/eswin_art_test"
    (cp $eswin_art_test_dir/* $TEST_DIR/backup/)
}

function start_emulator() {
    (xterm -e "emulator -show-kernel -no-window -no-accel -verbose -writable-system" &)
}

function art_test_config() {
    local eswin_art_test_dir=$(get_eswin_art_test_directory)
    local art_test_config=$eswin_art_test_dir/config.txt
    if [[ -e $art_test_config ]]; then
        (rm $art_test_config)
        (touch $art_test_config)
    else
        (touch $art_test_config)
    fi
    echo -e "\n请选择测试的种类， Gtest和Rtest都测试(all)[a], 只测试Gtest[g], 只测试rtest[r]\n"
    echo -e "配置文件保存在 $art_test_config\n"
    echo -e "请输入你的选择:\n"
    read INPUT_
    case $INPUT_ in
    "a")
        echo "ALL_TEST=YES" >>$art_test_config
        echo "GTEST=YES" >>$art_test_config
        echo "RTEST=YES" >>$art_test_config
        ;;
    "g")
        echo "ALL_TEST=NO" >>$art_test_config
        echo "GTEST=YES" >>$art_test_config
        echo "RTEST=NO" >>$art_test_config
        ;;
    "r")
        echo "ALL_TEST=NO" >>$art_test_config
        echo "GTEST=NO" >>$art_test_config
        echo "RTEST=YES" >>$art_test_config
        ;;
    *)
        echo "输入错误，再见！"
        return 1
        ;;
    esac
}

function check_env() {
    GREEN='\033[0;32m'
    RED='\033[0;31m'
    YELLOW='\033[0;33m'
    NC='\033[0m' # no color
    local T=$(gettop)
    local target_arch=$(get_target_arch)
    local product_image="$T/out/target/product/$target_arch/"

    if [[ $TERM_PROGRAM =~ "vscode" ]]; then
        echo "请不要使用vscode terminal做art测试，推荐使用Moba"
        return 1
    fi

    art_test_config

    if [[ $? != 0 ]]; then
        echo -e "配置文件选择不正确， 退出!"
        return 1
    fi
    echo -e "debug: target_arch is $product_image"
    if [ -d $product_image ]; then
        TEST_DIR=$(get_test_script_file_dir)
        backup_log_file
        echo -e "\n已经备份上次的art gtest和rtest原始log到$TEST_DIR/backup/"
        echo -e "\n${YELLOW}是否删除${NC} ${GREEN}$product_image${NC}以及使用 make -jx整编aosp? ${RED}请谨慎${NC}\n"
        echo -e "请键入${GREEN}Yes[y]${NC}, 或者${RED}No [n]${NC}"
        read INPUT_
        echo $INPUT_
        case $INPUT_ in
        "y")
            echo "需要编译aosp"
            ADB_STATUS=$(adb shell cat /system/build.prop)
            if [[ $? == 0 ]]; then
                echo -e "emulator已经启动，建议kill 已经运行的emulator(因为重新编译aosp嘛)\n"
                echo -e "如果是xterm启动的emulator(也就是之前运行该脚本启动的emulator)\n"
                echo -e "在ps命令中可能无法找到相关的进程，这时可以手动关掉xterm窗口就可以\n"
                return 1
            fi
            (
                rm -rf $product_image
                make -j16
            )
            if [[ $? != 0 ]]; then
                echo "编译aosp失败，请检查"
                return 1
            else
                echo "Aosp image 编译成功!"
                TEST_DIR=$(get_test_script_file_dir)
                eswin_art_test_dir="$T/out/target/product/$target_arch/eswin_art_test/"
                (
                    mkdir -p $eswin_art_test_dir
                    cp $TEST_DIR/backup/config.txt $eswin_art_test_dir
                )
                if [[ $? != 0 ]]; then
                    echo "复制文件失败，退出!"
                    return 1
                fi
                start_emulator
                echo "等待adb启动30s"
                sleep 30
                adb wait-for-device
            fi
            ;;
        "n")
            echo "不需要编译aosp"
            ADB_STATUS=$(adb shell cat /system/build.prop)
            if [[ $? != 0 ]]; then
                echo "emulator 没有启动，是否启动? Yes[y], No[n]\n"
                read ANS_
                if [[ $ANS_ == 'y' ]]; then
                    start_emulator
                    echo "等待adb启动60s"
                    sleep 60
                    adb wait-for-device
                else
                    return 1
                fi
            fi
            ADB_EX_=$(adb shell cat /system/build.prop)
            if [[ $? != 0 ]]; then
                echo "emulator 没有启动， 请确认"
                return 1
            fi
            echo "ADB is ok, 准备测试!"
            ;;
        *)
            echo "你的输入不正确， 再见!"
            return 1
            ;;
        esac
    else
        echo "应该编译$target_arch"
    fi

}
function run_gtest() {

    (compiled_art_test_target_and_host)

    (run_gtest_host)

    (run_art_target_gtest_test)

}
function run_art_test() {
    local line
    local art_test_config_file=$(get_art_test_config)

    check_env

    if [[ $? != 0 ]]; then
        echo -e "某些操作失败，再见!"
	return
    fi

    del_existing_files
    line=$(cat $art_test_config_file)
    if [[ $line =~ "ALL_TEST=YES" ]]; then
        echo "all test"
        run_gtest
        run_rtest_target
    elif [[ $line =~ "RTEST=NO" ]]; then
        echo "only gtest"
        run_gtest
    elif [[ $line =~ "GTEST=NO" ]]; then
        echo "only rtest"
        run_rtest_target
    fi
    execute_python_file
}
run_art_test
