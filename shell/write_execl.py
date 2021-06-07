#!/usr/bin/env python
# -*- coding: UTF-8 -*-

import sys
import xlwt
import datetime
import re
import string
import os
import subprocess
import time

gtest_sum = {}
rtest_sum = {}

timeout = 0
gtest_cnt = 0

compiler_model = "-speed-profile"
# global multi_case_str is default string to fill single case from multi
multi_args_str = "test-art-target-run-test-debug-prebuild" + compiler_model + "-no-relocate-ntrace-cms-checkjni-picimage-ndebuggable-no-jvmti-cdex-fast-"

# format cell display
# return dict
def set_cell_format():
    # set cell style
    # More info about xlwt, please refer to:
    # https://pydoc.net/xlwt/0.7.2/xlwt.Style/
    style = xlwt.XFStyle()
    pattern = xlwt.Pattern()
    pattern.pattern = xlwt.Pattern.SOLID_PATTERN # May be: NO_PATTERN, SOLID_PATTERN, or 0x00 through 0x12
    pattern.pattern_fore_colour = 43
    style = xlwt.XFStyle()
    style.pattern = pattern
    borders = xlwt.Borders()
    borders.left = 1
    borders.right = 1
    borders.top = 1
    borders.bottom = 1
    borders.bottom_colour=0x3A
    style.borders = borders
    style.alignment.horz = 0x02
    style.alignment.vert = 0x01
    style.alignment.wrap = 0x1
    # host case color
    pattern_host = xlwt.Pattern() # Create the Pattern
    pattern_host.pattern = xlwt.Pattern.SOLID_PATTERN # May be: NO_PATTERN, SOLID_PATTERN, or 0x00 through 0x12
    pattern_host.pattern_fore_colour = 1
    style_host = xlwt.XFStyle()
    borders.left = 1
    borders.right = 1
    borders.top = 1
    borders.bottom = 1
    borders.bottom_colour=0xA6
    style_host.borders = borders
    style_host.alignment.horz = 0x02
    style_host.alignment.vert = 0x01
    style_host.alignment.wrap = 0x1
    style_host.pattern = pattern_host
    # target name  color
    pattern = xlwt.Pattern() # Create the Pattern
    pattern.pattern = xlwt.Pattern.SOLID_PATTERN # May be: NO_PATTERN, SOLID_PATTERN, or 0x00 through 0x12
    pattern.pattern_fore_colour = 5
    style0 = xlwt.XFStyle()
    borders.left = 1
    borders.right = 1
    borders.top = 1
    borders.bottom = 1
    borders.bottom_colour=0x3A
    style0.borders = borders
    style0.alignment.horz = 0x02
    style0.alignment.vert = 0x01
    style0.alignment.wrap = 0x1
    style0.pattern = pattern
    ### case name color
    pattern1 = xlwt.Pattern() # Create the Pattern
    pattern1.pattern = xlwt.Pattern.SOLID_PATTERN # May be: NO_PATTERN, SOLID_PATTERN, or 0x00 through 0x12
    pattern1.pattern_fore_colour= 7
    style1 = xlwt.XFStyle()
    borders = xlwt.Borders()
    borders.left = 1
    borders.right = 1
    borders.top = 1
    borders.bottom = 1
    borders.bottom_colour=0x3A
    style1.borders = borders
    style1.alignment.horz = 0x02
    style1.alignment.vert = 0x01
    style1.alignment.wrap = 0x1
    style1.pattern = pattern1
    # failed color
    pattern2 = xlwt.Pattern() # Create the Pattern
    pattern2.pattern = xlwt.Pattern.SOLID_PATTERN # May be: NO_PATTERN, SOLID_PATTERN, or 0x00 through 0x12
    pattern2.pattern_fore_colour= xlwt.Style.colour_map['rose']
    style2 = xlwt.XFStyle()
    borders = xlwt.Borders()
    borders.left = 1
    borders.right = 1
    borders.top = 1
    borders.bottom = 1
    borders.bottom_colour=0x3A
    style2.borders = borders
    style2.alignment.horz = 0x02
    style2.alignment.vert = 0x01
    style2.alignment.wrap = 0x1
    style2.pattern = pattern2
    # slow color
    pattern3= xlwt.Pattern() # Create the Pattern
    pattern3.pattern = xlwt.Pattern.SOLID_PATTERN # May be: NO_PATTERN, SOLID_PATTERN, or 0x00 through 0x12
    pattern3.pattern_fore_colour= 47
    style3 = xlwt.XFStyle()
    borders = xlwt.Borders()
    borders.left = 1
    borders.right = 1
    borders.top = 1
    borders.bottom = 1
    borders.bottom_colour=0x3A
    style3.borders = borders
    style3.alignment.horz = 0x02
    style3.alignment.vert = 0x01
    style3.alignment.wrap = 0x1
    style3.pattern = pattern3
    # pass: green [0x11] Control from pattern4.pattern_fore_colour= 0x11
    pattern4= xlwt.Pattern() # Create the Pattern
    pattern4.pattern = xlwt.Pattern.SOLID_PATTERN # May be: NO_PATTERN, SOLID_PATTERN, or 0x00 through 0x12
    pattern4.pattern_fore_colour= 0x2A
    #pattern4.pattern_fore_colour = xlwt.Style.colour_map['dark_purple']
    #style.pattern = pattern
    style4 = xlwt.XFStyle()
    borders = xlwt.Borders()
    borders.left = 1
    borders.right = 1
    borders.top = 1
    borders.bottom = 1
    borders.bottom_colour=0x7f
    style4.borders = borders
    style4.alignment.horz = 0x02
    style4.alignment.vert = 0x01
    style4.alignment.wrap = 0x1
    style4.pattern = pattern4
    cell_format = {'style_pass':style4, 'style':style, 'style_yellow':style0, 'style_case_name':style1, 'style_fail':style2, 'style_slow':style3, 'style_host':style_host}
    return cell_format

def art_test_summary(sheet1):
    cell_format = set_cell_format()
    sheet1.row(1).height_mismatch = True
    sheet1.row(1).height = 720 # set 2nd line height
    # set col width
    sheet1.col(0).width = 256*50
    sheet1.col(1).width = 256*10
    sheet1.col(2).width = 256*10
    sheet1.col(3).width = 256*10
    sheet1.col(4).width = 256*10
    sheet1.col(5).width = 256*10
    sheet1.col(6).width = 256*10
    sheet1.col(7).width = 256*10
    sheet1.col(8).width = 256*15
    sheet1.col(9).width = 256*15
    # write datetime
    now_time = datetime.datetime.now()
    sheet1.write(0,0,"制表时间:" + datetime.datetime.now().strftime('%Y-%m-%d'),cell_format.get('style'))
    # target name
    Title = get_build_target()

    # get repo name
    proc = subprocess.Popen(['repo', 'info', '-l', 'art'],
                            stderr=subprocess.STDOUT,
                            stdout=subprocess.PIPE,
                            universal_newlines=True)
    repo_name = (proc.stdout.read().split('\n')[1].split('/')[-1])
    print (repo_name)
    Title = repo_name + ":" + "[" + Title + "]"
    sheet1.write_merge(0, 0, 1, 9, Title, cell_format.get('style_yellow'))
    sheet1_case_format_names=['','Total','Passed','Failed','Skipped','Empty','Timeout','Aborted','Start time', 'End time']
    j=0
    for case_format_name in sheet1_case_format_names:
        sheet1.write(1,j,case_format_name,cell_format.get('style_case_name'))
        j=j+1
    sheet1.row(0).height_mismatch = True
    sheet1.row(0).height = 800 # set 1st line height
    # note
    sheet1.write(6, 0,"说明：Art Gtest中Abort的程序及suite如下, 详情请见表2最后",cell_format.get('style_case_name'))

def write_gtest_summary_to_sheet1(sheet1):
    sum_flags=2
    cell_format = set_cell_format()
    sheet1.write(sum_flags, 0, 'art gtest summary', cell_format.get('style_case_name'))
    sheet1.write(sum_flags, 1, gtest_sum.get('gtest_total'), cell_format.get('style'))
    sheet1.write(sum_flags, 2, gtest_sum.get('gtest_passed'), cell_format.get('style_pass'))
    sheet1.write(sum_flags, 3, gtest_sum.get('gtest_failed'), cell_format.get('style_fail'))
    sheet1.write(sum_flags, 4, gtest_sum.get('gtest_skipped'), cell_format.get('style'))
    sheet1.write(sum_flags, 5, gtest_sum.get('gtest_empty'), cell_format.get('style_slow'))
    sheet1.write(sum_flags, 6, gtest_sum.get('gtest_timeout'), cell_format.get('style_fail'))
    sheet1.write(sum_flags, 7, gtest_sum.get('gtest_abort'), cell_format.get('style_fail'))

def write_rtest_summary_to_sheet1(sheet1):
    sum_flags = 3
    cell_format = set_cell_format()
    sheet1.write(sum_flags, 0, 'art rtest summary', cell_format.get('style_case_name'))
    sheet1.write(sum_flags, 1, rtest_sum.get('rtest_total'), cell_format.get('style'))
    sheet1.write(sum_flags, 2, rtest_sum.get('rtest_pass'), cell_format.get('style_pass'))
    sheet1.write(sum_flags, 3, rtest_sum.get('rtest_fail'), cell_format.get('style_fail'))
    sheet1.write(sum_flags, 4, rtest_sum.get('rtest_skip'), cell_format.get('style'))
    sheet1.write(sum_flags, 5, "normal:" + str(rtest_sum.get('rtest_normal')), cell_format.get('style_pass'))
    sheet1.write(sum_flags, 6, rtest_sum.get('rtest_timeout'), cell_format.get('style_fail'))

def get_build_target():
    return os.environ.get("TARGET_PRODUCT")

def generate_log():
    """ input file: art/test.py --target -r --interpreter -j64 2>&1 | tee -a art_test_log.txt
        output file: tmp.txt
        The input file is original file generated from command above. We get tmp log file which
        fill with "#### Start run test ###" string for dealing with data conveniently
    """
    rtest_log = get_log_file()
    
    try:
        os.remove("/tmp/rtest_log.txt")
    except OSError:
        print ("no rtest tmp file")

    with open(rtest_log.get('rtest_log')) as file_object:
        tmp_file = open("/tmp/rtest_log.txt", 'aw+')
        line = file_object.readline().strip()
        i = 0
        full_case_info = ""
        f = ''
        while line.strip(): 
            line_tmp = []
            #print (line)
            if '...' in line: # multi case string into a string
                if ']' in line:
                    if '=' in line:
                        break
                    complete_multi_case(line.strip(), tmp_file)
            elif '[' and ']' in line:
                line_full = line.split('\r')
                for chars in line_full:
                    if '[' in chars and ']' in chars:
                        line_tmp.append(chars)
                line_tmp[:] = [x for x in line_tmp if x]
                print (line_tmp)
                if len(line_tmp) != 100:
                    #print ("haha test")
                    for j in line_tmp:
                        if j:
                            print (j)
                            if "tests passed" in j:
                                pass
                            else:
                                complete_single_case(j.strip(), 's', tmp_file)
                        else:
                            pass
                elif "test-art-target" in line:
                    #for i in line
                    #print >> tmp_file, (line.strip())
                    print ("in other " + line)
                    complete_single_case(line.strip(), 's', tmp_file)
            elif  "tests passed" in line:
                print (line)
                pass
            i = i + 1
            line = file_object.readline()
        tmp_file.close()

def art_runtest_all(sheet3, sheet1):
    try:
        os.remove("/tmp/rtest_log.txt")
    except OSError:
        print ("no rtest tmp file")
    #process_runtest()
    generate_log()
    cell_format = set_cell_format()
    sheet3.row(0).height_mismatch = True
    sheet3.row(0).height = 720 # set 2nd line height
    # set col width
    sheet3.col(0).width = 256*5
    sheet3.col(1).width = 256*104
    sheet3.col(2).width = 256*20
    sheet3.col(3).width = 256*10
    sheet3.col(4).width = 256*10
    sheet3.col(5).width = 256*10
    sheet3_case_format_names=['ID', 'Case', 'Status','Passed','Failed','Skipped','Normal','Timeout']
    j=0
    for case_format_name in sheet3_case_format_names:
        sheet3.write(0,j,case_format_name, cell_format.get('style_case_name'))
        j=j+1
    rtest_pass_total = 0
    rtest_fail_total = 0
    rtest_skip_total = 0
    rtest_normal_total = 0
    rtest_timeout_total = 0
    with open('/tmp/rtest_log.txt') as file_object:
        line = file_object.readline().strip()
        i = 1
        while line:
            tmp = (line.strip())
            m = re.search(r'(?<=-)\d+', tmp)
            case_id = (m.group(0))
            tmp_list = tmp.split('-')
            case_status = tmp_list[-1]
            tmp_list.pop(0)
            case_name = "-".join(tmp_list)
            sheet3.write(i, 0, int(case_id), cell_format.get('style'))
            if case_status == "FAIL":
                sheet3.write(i, 1, case_name, cell_format.get('style_fail'))
                sheet3.write(i, 2, "FAIL", cell_format.get('style_fail'))
                rtest_fail_total = int(rtest_fail_total) + 1
                pass
            elif case_status == "PASS":
                sheet3.write(i, 1, case_name, cell_format.get('style_pass'))
                sheet3.write(i, 2, "PASS", cell_format.get('style_pass'))
                rtest_pass_total = int(rtest_pass_total) + 1
                pass
            elif case_status == "SKIP":
                sheet3.write(i, 1, case_name, cell_format.get('style_case_name'))
                sheet3.write(i, 2, "SKIP", cell_format.get('style_case_name'))
                rtest_skip_total = int(rtest_skip_total) + 1
                pass
            elif case_status == "NORMAL":
                rtest_normal_total = int(rtest_normal_total) + 1
                pass
            elif case_status == "TIMEOUT":
                sheet3.write(i, 1, case_name, cell_format.get('style_slow'))
                sheet3.write(i, 2, "TIMEOUT", cell_format.get('style_slow'))
                rtest_timeout_total += 1
                #print (line)
            i = i + 1
            line = file_object.readline()
        # descript run_test summary:
        sheet3.write(i, 1, "run_test summary", cell_format.get('style_case_name'))
        sheet3.write(i, 3, int(rtest_pass_total), cell_format.get('style_case_name'))
        sheet3.write(i, 4, int(rtest_fail_total), cell_format.get('style_case_name'))
        sheet3.write(i, 5, int(rtest_skip_total), cell_format.get('style_case_name'))
        sheet3.write(i, 6, int(rtest_normal_total), cell_format.get('style_pass'))
        sheet3.write(i, 7, int(rtest_timeout_total), cell_format.get('style_case_name'))
        rtest_total = rtest_pass_total + rtest_fail_total + rtest_skip_total + rtest_normal_total + rtest_timeout_total
        # descript run time
        rtest_log = get_log_file()
        rtest_cnt = 8
        with open(rtest_log.get('rtest_time')) as file_object:
            f = file_object.readline()
            while f:
                sheet1.write(3, rtest_cnt, f.split(' ')[-2], cell_format.get('style_yellow'))
                rtest_cnt += 1
                f = file_object.readline()
        global rtest_sum
        rtest_sum = {'rtest_total':rtest_total, 'rtest_pass':rtest_pass_total, 'rtest_fail':rtest_fail_total,'rtest_skip':rtest_skip_total,
        'rtest_normal':rtest_normal_total, 'rtest_timeout':rtest_timeout_total}
        write_rtest_summary_to_sheet1(sheet1)
        # rtest_fail_total rtest_skip_total rtest_normal_total)

def complete_multi_case(tmp_line, tmp_file):
    # Multi '\r' in a string
    test_id_t = tmp_line.split('\r')
    count = 0
    f = 0
    for i in test_id_t:
        if "[" in i:
            complete_single_case(i, 'm', tmp_file)

def extract_args(full_case_info):
    """
    Need to deal with string likes "['[', '99%', '1679/1682', ']',
     '...ntrace-cms-checkjni-picimage-ndebuggable-no-jvmti-cdex-fast-1001-app-image-regions64', 'SKIP']"
    """
    args_info = "test"
    n = re.search(r'(?<=-)\d+', full_case_info)
    full_case_num = n.group(0)
    full_case_list = full_case_info.split('-')
    full_num_index = full_case_list.index(full_case_num)
    for j in full_case_list[1:int(full_num_index)]:
        args_info = args_info + '-' + j
    multi_args_str = args_info

def complete_single_case(case_info, flags, tmp_file):
    """
    case_info: [ 92% 1548/1682 ] test-art-target-run-test-debug-prebuild-interpreter-no-relocate-ntrace-
                cms-checkjni-picimage-ndebuggable-no-jvmti-cdex-fast-623-checker-loop-regressions FAIL
            Use '-' conjoint case id and case status
    flags:  judge case was bring from which case[multi/single]
    """
    case_id = extract_data(case_info)
    if case_id == " ":
        return
    single_case = ""
    tmp = ""
    if flags == 's':
        extract_args(case_info)
        for i in  case_info.split(' ')[4:6]:
            single_case = single_case + '-' + i
        print >> tmp_file, ( case_id  + single_case)
    if flags == 'm':
        n = re.search(r'(?<=-)\d+', case_info.split(' ')[4])
        program_id_num = n.group(0)
        case_info_list = case_info.split('-')
        last_and_status = case_info_list[-1]
        program_id = case_info_list.index(program_id_num)
        for i in case_info_list[int(program_id):-1]:
           tmp = tmp + '-' + i
        tmp = tmp + '-' + last_and_status.split(' ')[0] + '-' + get_rtest_status(case_info)
        print >> tmp_file, ( case_id + '-' + multi_args_str  + tmp)

def get_rtest_status(log_entry):
    """ log_entry: 1. for half_case, like "[ 99% 1679/1682 ] ...ntrace-cms-checkjni-
                    picimage-ndebuggable-no-jvmti-cdex-fast-1001-app-image-regions64 SKIP"
    """
    # get last element of list
    return log_entry.split(' ')[-1]

def extract_data(tmp):
    k = []
    case_id = ""
    print (tmp)
    if tmp:
        case_id = tmp.split(' ', 4)[2]
        case_name = tmp.split(' ', 4)[4]
        case_id = case_id.split('/')[0]
    else:
        pass
    return case_id

def art_gtest_case_all(sheet3, sheet1):
    """ Write all gtest case into sheet3 classed by case.
    """
    cell_format = set_cell_format()
    sheet3.row(0).height_mismatch = True
    sheet3.row(0).height = 720 # set 2nd line height
    # set col width
    sheet3.col(0).width = 256*50
    sheet3.col(1).width = 256*50
    sheet3.col(2).width = 256*30
    sheet3.col(3).width = 256*10
    sheet3.col(4).width = 256*10
    sheet3.col(5).width = 256*10
    sheet3.col(6).width = 256*10
    sheet3.col(7).width = 256*10
    sheet3.col(8).width = 256*65
    sheet3.col(9).width = 256*65
    sheet3_case_format_names=['Program','Suite','Case','Status','time','DISABLE']
    j=0
    for case_format_name in sheet3_case_format_names:
        sheet3.write(0,j,case_format_name, cell_format.get('style_case_name'))
        j=j+1
    ## read txt
    gtest_log = get_log_file()
    global gtest_cnt
    try:
        os.remove(gtest_log.get('gtest_except_file'))
    except OSError:
        print ("no rtest gtest_except file")
    with open(gtest_log.get('gtest_log')) as file_object:
        f = file_object.read()
        blocks = f.split('#### Started')
        i = 1
        j = 7 # for sheet1 summary
        time_flags = 8
        sum_case_total = 0
        sum_case_passed = 0
        sum_case_failed = 0
        sum_case_skipped = 0
        sum_case_slow = 0
        sum_case_empty = 0
        sum_case_timeout = 0
        sum_case_abort = 0
        program_name = ''
        for b in blocks[1:] :
            lines = b.split('\n')
            if not lines[0]:
                break
            case_total = []
            suite_cnt = [0, 0]
            # Remove all empty chars in list
            lines[:] = [x for x in lines if x]
            # Abortd
            if " Started ####" in lines[0] and "#### Finished" in lines[1]:
                sheet3.write(i, 0, program_name, cell_format.get('style_yellow'))
                sheet3.write(i, 3, "Abort", cell_format.get('style_yellow'))
                program_name = lines[0].split(' ')[2]
                # deal with abort and disable
                with open(gtest_log.get('gtest_except_file'), "a+") as gtest_abort_file:
                    print >> gtest_abort_file, ("#### Start abort program case test ####")
                    print >> gtest_abort_file, (program_name)
                    print >> gtest_abort_file, ("#### End abort program case test ####")
            else:
                if "gtest-host run" in lines[0]:  # gtest_host test
                    program_name = lines[0].split(' ')[3]
                elif "Started ####" in lines[0]:
                    program_name = lines[0].split(' ')[2]
                    print ("in target " + program_name)
                sheet3.write(i, 0, program_name, cell_format.get('style_slow'))
                prev_line = ""
                for line in lines:
                    if "[==========] Running " in line:
                        suite_cnt = re.findall(r'\d+', line)[0]
                        sheet3.write(i, 1, "total " + str(suite_cnt) + " cases", cell_format.get('style_slow'))
                        i += 1
                    elif "[       OK ]" in line and "[  INFO ]" not in line:  # Need to to [  INFO ] art/libartbase/base/membarrier_test.cc:68:: art::MembarrierCommand::kRegisterPrivateExpeditedSyncCore[       OK ] membarrier.private_expedited_sync_core (4 ms)
                        line_status = judge_gtest_status(line, 'p')
                        sheet3.write(i, 1, line_status[1], cell_format.get('style_pass'))
                        sheet3.write(i, 2, line_status[0], cell_format.get('style_pass'))
                        sheet3.write(i, 3, "OK", cell_format.get('style_pass'))
                        sheet3.write(i, 4, line_status[2] + " ms" , cell_format.get('style_pass'))
                        sum_case_passed += 1
                        i += 1
                    elif "skipping" in line:  # Need to to [  INFO ] art/libartbase/base/membarrier_test.cc:68:: art::MembarrierCommand::kRegisterPrivateExpeditedSyncCore[       OK ] membarrier.private_expedited_sync_core (4 ms)
                        print (line)
                        line_status = extra_skipping_info(prev_line.split(' '))
                        sheet3.write(i, 1, line_status[0], cell_format.get('style_fail'))
                        sheet3.write(i, 2, line_status[1], cell_format.get('style_fail'))
                        sheet3.write(i, 3, "Skipped", cell_format.get('style_fail'))
                        sum_case_skipped += 1
                        i += 1
                    elif "[  FAILED  ]" in line and '(' in line:
                        line_status = judge_gtest_status(line, 'p')
                        sheet3.write(i, 1, line_status[1], cell_format.get('style_fail'))
                        sheet3.write(i, 2, line_status[0], cell_format.get('style_fail'))
                        sheet3.write(i, 3, "FAILED", cell_format.get('style_fail'))
                        sheet3.write(i, 4, line_status[2] + " ms" , cell_format.get('style_fail'))
                        sum_case_failed += 1
                        i += 1
                    elif '[ RUN      ]' in prev_line and "#### Finished" in line:
                        line_status = judge_gtest_status(prev_line, 'a')
                        sheet3.write(i, 1, line_status[1], cell_format.get('style_yellow'))
                        sheet3.write(i, 2, line_status[0], cell_format.get('style_yellow'))
                        sheet3.write(i, 3, "Abort", cell_format.get('style_yellow'))
                        sheet1.write(j, 0, program_name + line_status[1] + '.' + line_status[0], cell_format.get('style_yellow'))
                        with open(gtest_log.get('gtest_except_file'), "a+") as gtest_abort_file:
                            print >> gtest_abort_file, ("#### Start abort program case test ####")
                            print >> gtest_abort_file, (program_name)
                            print >> gtest_abort_file, ("#### End abort program case test ####")
                        sum_case_abort += 1
                        i += 1
                        j += 1
                    elif '[  PASSED  ]' in line and str(re.findall(r'\d+', line)[0]) == '0':
                        sheet3.write(i, 1, "0", cell_format.get('style_yellow'))
                        sheet3.write(i, 2, "0", cell_format.get('style_slow'))
                        sheet3.write(i, 3, " ", cell_format.get('style_fail'))
                        sum_case_empty += 1
                        i += 1
                    elif 'YOU HAVE ' in line:
                        sheet3.write(i, 1, program_name, cell_format.get('style_yellow'))
                        sheet3.write(i, 5, re.findall(r'\d+', line)[0], cell_format.get('style_slow'))
                        sheet3.write(i, 3, "DISABLE", cell_format.get('style_yellow'))
                        i += 1
                    elif '_MY_TIME_' in line:
                        sheet1.write(2, time_flags, line.split(' ')[-2], cell_format.get('style_yellow'))
                        time_flags += 1
                        break
                    prev_line = line
                    gtest_cnt = i
        sum_case_total = sum_case_passed + sum_case_abort + sum_case_failed + sum_case_skipped + sum_case_slow + sum_case_timeout + sum_case_empty
        global gtest_sum
        gtest_sum = {'gtest_total':sum_case_total, 'gtest_passed':sum_case_passed, 'gtest_failed':sum_case_failed, 'gtest_skipped':sum_case_skipped, 'gtest_slow':sum_case_slow, 'gtest_timeout':sum_case_timeout, 'gtest_abort':sum_case_abort, 'gtest_empty':sum_case_empty}
        write_gtest_summary_to_sheet1(sheet1)

def extra_skipping_info(info_list):
    print (info_list)
    ret = []
    if "OK" not in info_list:
        print ("ok")
        for program_case in info_list[8:9]:
            for i in program_case.split('.'):
                ret.append(i.strip())
    else:
        ok_index = info_list.index('OK')
        for program_case in (info_list[int(ok_index)+2 : int(ok_index)+3]):
            for i in program_case.split('.'):
                ret.append(i.strip())
    return (ret)
    
def judge_gtest_status(gtest_list, flags):
    """ args:
    [       OK ] AssemblerRiscv64Test.LoadFpuFromOffset (78 ms)
    """
    ret = []
    line = gtest_list.split(' ')
    line[:] = [x for x in line if x]
    #print (line)
    case_name = line[3].split('.')[1]
    suite_name = line[3].split('.')[0]
    ret.append(case_name)
    ret.append(suite_name)
    if flags == 'p':
        pass_time = re.findall(r'\d+', str(line[4]))
        ret.append(pass_time[0])
    elif flags == 'a':
        pass
    return ret

def get_log_file():
    current_dir = os.getcwd()
    product_target =  os.environ.get("OUT").split('/')[-1]
    eswin_art_test_dir = current_dir + "/out/target/product/" + product_target + "/eswin_art_test/"
    gtest_log_file = eswin_art_test_dir + "gtest_tmp_run_log.txt"
    gtest_except = eswin_art_test_dir + "gtest_except.txt"
    rtest_log_file = eswin_art_test_dir + "rtest_tmp_run_log.txt"
    rtest_time = eswin_art_test_dir + "rtest_time.txt"
    art_test_config = eswin_art_test_dir + "config.txt"
    log_files = {'config_file':art_test_config,'gtest_log':gtest_log_file,'gtest_except_file': gtest_except, 'rtest_log':rtest_log_file, 'rtest_time':rtest_time}
    return log_files

def layout_execl():
    """
    # sheet1: art_test_summary
    # sheet2: gtest_all
    # sheet3: runtest_all
    config_file" tell the python program to excute which art test *MUST BE HAVE IT*
    eg: ALL_TEST=YES
        GTEST=YES
        RTEST=YES
    """
    gtest_log = get_log_file()

    wbk = xlwt.Workbook(encoding='utf-8')
    sheet1 = wbk.add_sheet("art_test_summary", cell_overwrite_ok=True)
    art_test_summary(sheet1)

    with open(gtest_log.get('config_file')) as file_object:
         line = file_object.readline().strip()
         while line:
            print(line)
            if "ALL_TEST=YES" in line:
                print ("Run all test")
                sheet3 = wbk.add_sheet("art_gtest_case_all", cell_overwrite_ok=True)
                art_gtest_case_all(sheet3, sheet1)
                sheet4 = wbk.add_sheet("art_runtest_all", cell_overwrite_ok=True)
                art_runtest_all(sheet4, sheet1)
            if "RTEST=NO" in line:
                print ("only gtest")
                sheet3 = wbk.add_sheet("art_gtest_case_all", cell_overwrite_ok=True)
                art_gtest_case_all(sheet3, sheet1)
            if "GTEST=NO" in line:
                print ("only rtest")
                sheet4 = wbk.add_sheet("art_runtest_all", cell_overwrite_ok=True)
                art_runtest_all(sheet4, sheet1)
            line = file_object.readline().strip()

    wbk.save(datetime.datetime.now().strftime("art_test_UT-"+'%Y-%m-%d'+'.xls'))

def get_except_gtest_name(program): # details abort case for the time
    gtest_except = '/data/nativetest64/' + program
    proc = subprocess.Popen(['adb', 'shell', gtest_except],
                            stderr=subprocess.STDOUT,
                            stdout=subprocess.PIPE,
                            universal_newlines=True)
    try:
        os.remove("/tmp/abort_rtest_log.txt")
    except OSError:
        print ("no /tmp/abort_rtest_log.txt file")
    abort_file = open("/tmp/abort_rtest_log.txt", 'a+')
    output = proc.stdout.read()
    print >> abort_file, ("#### Start abort program case test ####")
    if output == "":
        print >> abort_file, ("[==========] Running 1 test from 1 test suite.").strip()
        print >> abort_file, ("__empty__").strip()
    print >> abort_file, (output)
    print >> abort_file, ("#### End abort program case test ####")
    abort_file.close()


filter_const = "--gtest_filter=-"
filter_list = []
abort_cnt = 0

def call_subprocess(i, line, filter_case):
    global filter_list, filter_const
    #filter_test = filter_case
    print (filter_const)
    program = '/data/nativetest64/' + line
    #print ("debug in call_" + program + filter_const)
    program_filter = program + ' ' + filter_const
    print ("debug ca " + program_filter)
    proc = subprocess.Popen(['adb', 'shell', program_filter],
                            stderr=subprocess.STDOUT,
                            stdout=subprocess.PIPE,
                            universal_newlines=True)
    if filter_case == '__empty__':
        output = '__empty__'
    else:
        output = proc.stdout.read()
    print (output)
    try:
        os.remove("/tmp/2_rtest_log.txt")
    except OSError:
        print ("No /tmp/2_rtest_log.txt")
    abort_file = open("/tmp/2_rtest_log.txt", 'a+')
    print >> abort_file, ("#### Start abort program case test ####")
    print >> abort_file, (output)
    print >> abort_file, ("#### End abort program case test ####")
    abort_file.close()


def get_output(program):
    with open("/tmp/abort_rtest_log.txt") as file_object:
        f = file_object.read()
        blocks = f.split('#### Start')
        #print (blocks)
        case_total = blocks[1].split('\n')[1].split(' ')[2]
        blocks = blocks[1].split('\n')
        blocks[:] = [x for x in blocks if x]
        line_prev = blocks[0]
        file_object.close()
        global abort_cnt
        i = 0
        cout  = 0
        for i in range(int(case_total)):
            global filter_list, filter_const
            if i == 0:
                print (i)
                for line in blocks[1:]:
                    pass
                    if "[       OK ]" in line_prev:
                        cout += 1
                    if (" (core dumped) " in line or "#### End abort " in line ) and "[ RUN      ]" in line_prev: # Case is aborted, there is have interesting thing
                        filter_case = line_prev.split(' ')[8]
                        filter_const += str(filter_case)
                        #print ("debug get_output for  " + line)
                        #print (filter_const)
                        call_subprocess(i, program, filter_const)
                    if "__empty__" in line:
                        print ("=====" + line)
                        call_subprocess(i, program, "__empty__")
                        break
                    line_prev = line
                    #print (i)
            else:
                with open("/tmp/2_rtest_log.txt", 'a+') as log_file:
                    f = log_file.read()
                    blocks = f.split('#### Start')
                    print (blocks)
                    blocks = blocks[1].split('\n')
                    blocks[:] = [x for x in blocks if x]
                    line_prev = blocks[0]
                    log_file.close()
                    ok_cnt = 0
                    for line in blocks[1:]:
                        if " (core dumped) " in line and "[ RUN      ]" in line_prev: # Case is aborted
                            filter_case = line_prev.split(' ')[8].strip()
                            filter_const = filter_const + ':' + str(filter_case)
                            print (filter_case)
                            call_subprocess(i, program, filter_const)
                            abort_cnt += 1
                        #line_prev = line
                        if "Trap " in line and "[ RUN      ]" in line_prev: # Case is aborted
                            filter_case = line_prev.split(' ')[8]
                            filter_const = filter_const + ':' + str(filter_case)
                            print (filter_case)
                            call_subprocess(i, program, filter_case)
                            abort_cnt += 1
                        #line_prev = line
                        if "[       OK ]" in line:
                            ok_cnt += 1
                        line_prev = line
            i += cout
        print ("abort cout is %d " + str(abort_cnt))

def deal_with_gtest_except(sheet3):
    global gtest_const
    loop_wait()
    log_file = get_log_file()
    try:
        os.remove('/tmp/2_rtest_log.txt')
    except OSError:
        print ('No /tmp/2_rtest_log.txt')
    gtest_abort_program = []
    with open(log_file.get('gtest_except_file')) as fd:
        line = fd.readline()
        while line:
            if "####" not in line:
                gtest_abort_program.append(line)
            line = fd.readline()
        print (gtest_abort_program)
        for i in gtest_abort_program:
            try:
                os.remove("/tmp/2_rtest_log.txt")
            except OSError:
                print ("no /tmp/2_rtest_log.txt")
            initialize_filter_const()
            get_except_gtest_name(i.strip())
            get_output(i.strip())
            write_gtest_except_execl(sheet3, i.strip())

def initialize_filter_const():
    global filter_const
    filter_const = "--gtest_filter=-"

def write_gtest_except_execl(sheet3, program):
    global gtest_cnt
    cell_format = set_cell_format()
    i = gtest_cnt + 4
    sheet3.write(gtest_cnt + 2, 0, "========================", cell_format.get('style_yellow'))
    sheet3.write(gtest_cnt + 3, 0, "Abort gtest case details", cell_format.get('style_yellow'))
    sheet3.write(i, 0, program, cell_format.get('style_case_name'))
    with open("/tmp/2_rtest_log.txt") as fd:
        line = fd.readline().strip()
        while line:
            #print (line)
            if "[       OK ]" in line:
                ok_case = (line.strip('\n').split(' '))
                ok_case[:] = [x for x in ok_case if x]
                sheet3.write(i, 1, ok_case[3].split('.')[0], cell_format.get('style_case_name'))
                sheet3.write(i, 2, ok_case[3].split('.')[1], cell_format.get('style_case_name'))
                sheet3.write(i, 3, "OK", cell_format.get('style_pass'))
                i += 1
            if "Note: Google Test filter" in line:
                print (line)
                abort_case = line.strip('\n').split(':')[1:]
                print ("debug Note: abort_case\n" )
                print (abort_case)
                for j in abort_case:
                    sheet3.write(i, 1, j.split('.')[0], cell_format.get('style_case_name'))
                    sheet3.write(i, 2, j.split('.')[1], cell_format.get('style_case_name'))
                    sheet3.write(i, 3, "Abort", cell_format.get('style_fail'))
                    i += 1
            line = fd.readline()
    gtest_cnt = i

def loop_wait():
    program_filter = ' '
    proc = subprocess.Popen(['adb', 'shell', program_filter],
                            stderr=subprocess.STDOUT,
                            stdout=subprocess.PIPE,
                            universal_newlines=True)
    output = proc.stdout.read()
    print (output)

def main():
    layout_execl()
    #generate_log()

if __name__ == "__main__":
    main()
