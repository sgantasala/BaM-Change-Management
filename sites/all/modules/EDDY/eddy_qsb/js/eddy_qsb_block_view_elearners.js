
var depend = {};
depend['Category'] = {};
depend['EduLevel'] = {};
depend['Category'][0] = [[true, true], ['', '', '']]; // 2 levels
depend['EduLevel'][1] = [[true, true], [true, false, true]]; //3 dropdown, edulevel is the first
depend['Category'][1] = [[true, true], [true, false, true]]; //3 dropdown, category is the first


// var depend = [[true,true],[true,false,true]];
// var depend_2 = [[true,true], ['','','']];
// depend[0][0] = true; //second field first load depends on first field
// depend[0][1] = true; //second field depends on first field onchange
// depend[1][0] = false; //third field first load NOT depends on first field
// depend[1][1] = false; //third field depends on first field onchange
// depend[1][2] = true; //third field depends on second field onchange


function get_val_1(ask_val, ask_r_val, question_level) {
    return ask_val;
}
function get_val_2(ask_val, ask_r_val, question_level) {
    return ask_val;
}
function get_val_3(ask_val, ask_r_val, question_level) {
    return ask_val;
}


