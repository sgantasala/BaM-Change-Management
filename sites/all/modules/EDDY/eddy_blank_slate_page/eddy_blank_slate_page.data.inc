<?php
function _get_eddy_form_option_list()
{
    $options = array();
    try
	{
        $eddy_form_list = _get_eddy_form_list();
        if(count($eddy_form_list)>0){
            foreach($eddy_form_list as $k => $v)
            {
                $options[$v->id] = $v->name;
            }
        }
    }
	catch(Exception $e)
	{
		watchdog_exception('_get_eddy_form_option_list', $e);
	}
    return  $options;
}

function _get_eddy_form_list()
{
    $eddy_form_list = array();
    try
	{
        $eddy_form_list = db_select('eddy_forms_engine', 'ef')->fields('ef')->execute()->fetchAll();
    }
	catch(Exception $e)
	{
		watchdog_exception('gs_oas_ads', $e);
	}
    return  $eddy_form_list;
}


function _get_institutions_option_list()
{
    $options = array();
    try
	{
        $list = _get_institutions_from_is();
        if(count($list)>0){
            foreach($list as $k => $v)
            {
                $options[$v->InstitutionId] = $v->Name;
            }
        }
    }
	catch(Exception $e)
	{
		watchdog_exception('_get_institutions_option_list', $e);
	}
    return  $options;
}

function _get_institutions_from_is(){


    $result = array();
    try{
        db_set_active('nexus');
        $result = db_query('SELECT distinct i.InstitutionId, i.Name FROM Prod.VW_Matching_ProgramProduct_Prod p LEFT JOIN Institution i ON i.InstitutionId = p.InstitutionId where p.InstitutionId NOT IN (3,4) ORDER BY i.Name')->fetchAll();
        db_set_active();
    }
    catch(Exception $e){

        db_set_active();

        watchdog_exception("Institution from IS: Get Institution from IS", $e, "", WATCHDOG_ERROR);

    }

    return $result;

}