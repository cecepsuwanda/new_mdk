<?php
require_once 'default_table.class.inc';
//require_once 'query_string.class.inc';
class tb_gen extends Default_Table
{
	// additional class variables go here
	function __construct($tb_name)
	{
		if(!in_array($tb_name,array('jmlkk_jmljiwa_stat','tbgen'))){	

			$this->tablename       = $tb_name;        		
			$this->fieldlist       = $this->getfieldlist();
        }

        switch ($tb_name){
		 case 'jmlkk_jmljiwa_stat' :
		                            $this->sql_select = 'kd_subdist,SUM(kd_fammbrtyp=1) AS jmlkk,COUNT(*) AS jmljiwa'; 
		                            $this->sql_from = 'dbo_family a inner join dbo_individu b on a.kd_fam=b.kd_fam';
		                            $this->sql_where = "kd_dist='1017'";
		                            $this->sql_groupby = 'kd_subdist';
                                    $this->sql_orderby = 'kd_subdist';
                                    //,SUM(kd_fammbrtyp=1 and kd_prosplvl=1) AS jmlpra,SUM(kd_fammbrtyp=1 and kd_prosplvl=2) AS jmlks,SUM(kd_fammbrtyp=1 and kd_prosplvl=3) AS jmlks1
		                            break;
		  case 'dbo_kategori'      : $this->fieldlist['Kd_prosplvl'] = array('pkey' => 'y'); 
		                             $this->fieldlist['id_ind_ks'] = array('pkey' => 'y'); 
		                             break;                    
		  case 'tbgen' : break;                          
		                   
		}              
		
	} // end class constructor

} // end class


?>