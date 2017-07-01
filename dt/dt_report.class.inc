<?php require_once('shared.php');
     
class dt_report
{
   private $arr_ks;
   private $arr_ks_b;
   private $arr_ks_bb;

   function __construct() {
		
   }

	private function gettoday()
	{
		$d=date('j'); 
		$m=date('n'); 
		$y=date('Y'); 
		
		if($d<10)
		$d="0".$d;
		if($m<10)
		$m="0".$m;

		return array('d'=>$d,'m'=>$m,'y'=>$y);
	}

	private function getrentang($awal,$akhir=0,$pref='')
	{
		$tgl = $this->gettoday();           

		$y_awal=$tgl['y']-$awal;              	  
		$uq_awal=$y_awal."-".$tgl['m']."-".$tgl['d'];

		$y_akhir=$tgl['y']-($akhir+1);              	  
		$uq_akhir=$y_akhir."-".$tgl['m']."-".$tgl['d'];

		if($akhir==0){
			return ($pref!=''? $pref.'.' : '')."Tgl_lahir <= '$uq_awal'";
		}else{
			return ($pref!=''? $pref.'.' : '')."Tgl_lahir <= '$uq_awal' AND ".($pref!=''? $pref.'.' : '')."Tgl_lahir > '$uq_akhir'";
		} 
	} 


   private function getkdwl($idkec,$iddesa,$iddusun,$idrt,$pref='',$opt='AND',$field='')
	{
		$kd_wl='';
		if($idrt)
		{
			$kd_wl=($pref!=''? $pref.'.':'')."Kd_neigh='$idrt' $opt";
			$kd=$idrt; 
		}
		elseif($iddusun)
		{
			$kd_wl=($pref!=''? $pref.'.':'')."Kd_subvill='$iddusun' $opt"; 
			$kd=$iddusun; 
		}
		elseif($iddesa)
		{
			$kd_wl=($pref!=''? $pref.'.':'')."Kd_vill='$iddesa' $opt"; 
			$kd=$iddesa;
		}
		elseif($idkec)
		{
			$kd_wl=($pref!=''? $pref.'.':'')."Kd_subdist='$idkec' $opt";
			$kd=$idkec; 
		}else{
			$kd_wl=($pref!=''? $pref.'.':'')."Kd_dist='1017' $opt";
			$kd=1017;	
		}

		if(!empty($field))
		{
			$kd_wl=($pref!=''? $pref.'.':'')."$field='$kd' $opt";
		}


		return $kd_wl;		
	}

	private function build_rc($data)
	{
		$rc=array();
		if(!empty($data))
		{
			foreach($data as $row)
			{
				foreach($row as $key=>$v)
				{ 
					$rc[$key]=$v;                    
				}
			}
		}

		return $rc;		  
	}

	private function check_var($jml,$idx_jml)
  {
    $op=0;
      if(is_array($jml))
      {         
         if(is_array($idx_jml))
         {
            $tmp=$jml;
            $idx_ada = true;
            foreach ($idx_jml as $idx) {
              if($idx_ada){
                if(isset($tmp[$idx])){   
                  $tmp=$tmp[$idx];
                 }else{
                   $idx_ada=false;
                 }
              }    
            }
            if($idx_ada){
             $op=$tmp;
            }
         }else{
           $op=isset($jml[$idx_jml]) ? $jml[$idx_jml] : 0;
         }
      }else{
        if(!empty($jml)){
         $op=$jml;
        }
      }

      return $op;
  }


  private function fjml_ttl($jml,$idx_jml,$dt,$idx_dt)
	{
  		$op1=$this->check_var($jml,$idx_jml);
      $op2=$this->check_var($dt,$idx_dt);
      $tmp_jml = $op1+$op2;
    return $tmp_jml;		
	}

  private function fprosen($dt1,$idx_dt1,$dt2,$idx_dt2,$kali=100)
  {
    
    $op1=$this->check_var($dt1,$idx_dt1);
    $op2=$this->check_var($dt2,$idx_dt2);
    $tmp_prosen = ($op2 !=0 ? round((($op1/$op2)*$kali),2) : 0 );

    /*if($idx_dt1=='' and $idx_dt2==''){
      $tmp_prosen = ($dt2 !=0 ? round((($dt1/$dt2)*$kali),2) : 0 );
    }elseif($idx_dt2==''){
      $tmp_prosen = ($dt2 !=0 ? round((($dt1[$idx_dt1]/$dt2)*$kali),2) : 0 );
    }
    else{
      $tmp_prosen = ($dt2[$idx_dt2] !=0 ? round((($dt1[$idx_dt1]/$dt2[$idx_dt2])*$kali),2) : 0 );       
    }*/

    return $tmp_prosen;
  }

  private function frupiah($dt,$idx,$digit=0)
  {
       if($idx=='')
       {
         $txt = number_format($dt,$digit,',','.');
       }else{
        $txt = number_format((isset($dt[$idx]) ? $dt[$idx] : 0),$digit,',','.');
       }

       return $txt;
  }
 

  private function arrayks()
  {
    $this->arr_ks['pra_s']="Kd_prosplvl=1 OR Kd_prosplvl=6";
    $this->arr_ks['ks_1']="Kd_prosplvl=2 OR Kd_prosplvl=7";
    $this->arr_ks['ks_2']="Kd_prosplvl=3";
    $this->arr_ks['ks_3']="Kd_prosplvl=4";
    $this->arr_ks['ks_3_p']="Kd_prosplvl=5";
    
    $this->arr_ks_b['pra_s']="PRA S";
    $this->arr_ks_b['ks_1']="KS I";
    $this->arr_ks_b['ks_2']="KS II";
    $this->arr_ks_b['ks_3']="KS III";
    $this->arr_ks_b['ks_3_p']="KS III+";
    
    $this->arr_ks_bb['pra_s']="pra_s";
    $this->arr_ks_bb['ks_1']="ks_1";
    $this->arr_ks_bb['ks_2']="ks_2";
    $this->arr_ks_bb['ks_3']="ks_3";
    $this->arr_ks_bb['ks_3_p']="ks_3_p";
  }

   function getdtmenu01($idkec,$iddesa,$iddusun,$idrt,$pageno,$rows_per_page,$where,$order){ 
		
		$col = array(0=>'a.Kd_fam',1=>'a.nama',2=>'b.jml');

		$kd_wl=$this->getkdwl($idkec,$iddesa,$iddusun,$idrt);
		
		$tb = new tb_gen('tbgen');
		$tb->sql_from='vw_fam_indv a inner join (select kd_fam,count(kd_fam) as jml from dbo_individu group by kd_fam) b on a.kd_fam=b.kd_fam';
		$tb->sql_select = "a.Kd_fam,a.nama,b.jml"; 
		$tb->sql_groupby = 'a.Kd_fam';
		if(!empty($order)){
		  $tb->sql_orderby = $col[$order[0]].' '.$order[1]; 
		}
        
        $tb->pageno = $pageno;
        $tb->rows_per_page = $rows_per_page;
		
		$sql_txt = "$kd_wl Kd_fammbrtyp=1 and Kd_mutasi IS NULL";		
		if((!empty($where)) and (!empty($_SESSION['sql_txt'])) and ($_SESSION['sql_txt']==$sql_txt)){           
           $jmltotaldata = $_SESSION['jmltotaldata'];
		}else{  
		  $data = $tb->getData($sql_txt);
          $jmltotaldata = $tb->numrows;
          $jmldisplaydata = $tb->numrows;
          $_SESSION['sql_txt']=$sql_txt;
          $_SESSION['jmltotaldata']=$jmltotaldata;
        }         
        //$tb_indv = new tb_gen('dbo_individu');  
		//$tb_indv->sql_select = "Nama";
       if(!empty($where)){ 
		  $str = " AND ((a.nama LIKE '%$where%') or (a.Kd_fam LIKE '%$where%') or (b.jml like '%$where%'))";
          $data = $tb->getData("$kd_wl Kd_fammbrtyp=1 and Kd_mutasi IS NULL $str");
          $jmldisplaydata = $tb->numrows;		  
       }

    $tmp_data=array();
    if(!empty($data))
    {
      foreach ($data as $row) {
        $tmp_row = array();
        $tmp_row[] = $row['Kd_fam'];

        //$tb_indv->getData("Kd_fam='$row[Kd_fam]'");			
		//$jml = $tb_indv->numrows;     

		$tmp_row[]=$row['nama'];
        $tmp_row[] = $row['jml'];

        $tmp_data[]=$tmp_row;
      }
    }

		return  array('totaldata'=>$jmltotaldata,'displaydata'=>$jmldisplaydata,'data'=>$tmp_data); 
	}


	function getdtmenu02_tab1($idkec,$iddesa,$iddusun,$idrt){
        
        $kd_wl=$this->getkdwl($idkec,$iddesa,$iddusun,$idrt);
        
        $tb = new tb_gen('tbgen');		
		$tb->sql_from= 'vw_fam_indv';
		$tb->sql_select= 'kd_fam,
                          Nama,
                          IF(kd_gen=1,1,0) AS jkl,
                          IF(kd_gen=2,1,0) AS jkp,
                          IF(kd_emp<>6,1,0) AS krj,
                          IF(kd_emp=6,1,0) AS tkrj,
                          IF(kd_martl=2,1,0) AS stat,
                          IF(kd_martl<>2,1,0) AS tsat,
                          IF(kd_edu=2,1,0)AS edu1,
                          IF((kd_edu=3 OR kd_edu=5),1,0) AS edu2,
                          IF(kd_edu=7,1,0) AS edu3,
                          IF(kd_edu=9,1,0) AS edu4,
                            Kd_prosplvl';
        $tb->sql_orderby = 'kd_fam';
        $tb->sql_groupby = 'kd_fam';
        $data = $tb->getData("$kd_wl kd_fammbrtyp=1 AND kd_mutasi IS NULL");
        
        $u1549 = $this->getrentang(15,49);
        $u01 = $this->getrentang(0,1);
        $u15 = $this->getrentang(1,5);
        $u56 = $this->getrentang(5,6);
        $u712 = $this->getrentang(7,12);
        $u1315 = $this->getrentang(13,15);
        $u1621 = $this->getrentang(16,21);
        $u2259 = $this->getrentang(22,59);
        $u60 = $this->getrentang(60);

        $u020 = $this->getrentang(0,20);
        $u2029 = $this->getrentang(20,29);
        $u3049 = $this->getrentang(30,49);

        $tb2 = new tb_gen('tbgen');		
		$tb2->sql_from= 'vw_fam_indv';
		$tb2->sql_select = "IF(Bantuan_modal='1',1,0) AS modal1,
                            IF(Bantuan_modal='0',1,0) AS modal0, 
                            SUM(kd_gen=1) AS jl,
                            SUM(kd_gen=2) AS jp,
                            sum((kd_gen=2) and ($u1549)) AS usbr,
                            0 as one,0 as two,
                            sum((posyandu=1) and ($u01)) as u01pos,
                            sum((posyandu=0) and ($u01)) as u01npos,
                            sum((posyandu=1) and ($u15)) as u15pos,
                            sum((posyandu=0) and ($u15)) as u15npos,
                            sum($u56) as u56,
                            sum((kd_edu<>0) and (kd_gen=1) and ($u712)) as u712edul,
                            sum((kd_edu<>0) and (kd_gen=2) and ($u712)) as u712edup,
                            sum((kd_edu=0) and (kd_gen=1) and ($u712)) as u712nonedul,
                            sum((kd_edu=0) and (kd_gen=2) and ($u712)) as u712nonedup,
                            sum((kd_edu<>0) and (kd_gen=1) and ($u1315)) as u1315edul,
                            sum((kd_edu<>0) and (kd_gen=2) and ($u1315)) as u1315edup,
                            sum((kd_edu=0) and (kd_gen=1) and ($u1315)) as u1315nonedul,
                            sum((kd_edu=0) and (kd_gen=2) and ($u1315)) as u1315nonedup,
                            sum($u1621) as u1621,
                            sum($u2259) as u2259,
                            sum($u60) as u60,
                            0 as three";
        $tb2->sql_groupby = 'kd_fam';                         
        
        $tb_contr_src = new tb_gen('dbo_contr_src');
        $dt_contr_src = $tb_contr_src->getData('');

       $str='';
       if(!empty($dt_contr_src))
       {
          foreach ($dt_contr_src as $row) {
            $str.=  (!empty($str) ? ',' : '')."if((pus='1' and Kd_nonacptr is null and  Kd_consrc=$row[Kd_consrc]),singkatan,'') as consrc$row[Kd_consrc]";
          }
       }

       $str.=",if((pus='1' and Kd_nonacptr is null and a.Kd_contyp=4),1,0) as consrc";
          
        $dt_non = new dt_non_acptr_reas;
        $data_non = $dt_non->getdata('');
        
        $str1='';
        if(!empty($data_non))
        {
        	foreach ($data_non as $row) {
        	  $str1.=  (!empty($str1) ? ',' : '')."if(Kd_nonacptr=$row[Kd_nonacptr],1,0) as nonacptr$row[Kd_nonacptr]";	
        	}
        }

        $tb3 = new tb_gen('tbgen');		
		$tb3->sql_from= 'vw_fam_indv a left join dbo_contr_typ b on a.Kd_contyp=b.Kd_contyp';
		$tb3->sql_select= "nama, if($u020,YEAR(NOW())-YEAR(Tgl_lahir),'') as u1,
		                         if($u2029,YEAR(NOW())-YEAR(Tgl_lahir),'') as u2,
		                         if($u3049,YEAR(NOW())-YEAR(Tgl_lahir),'') as u3,
		                         $str,$str1";
        $tb3->sql_groupby = 'kd_fam';
        $tb3->sql_orderby = 'kd_fam';  

        $tmp_dt_tb=array();
        $arrjml = array();
        if(!empty($data))
        {
           $nombrs=1;
           foreach ($data as $row) {
           	$tmp=array();
           	$tmp[] = $nombrs;
           	$Kd_prosplvl = $row['Kd_prosplvl'];
           	$i=1;           	
           	foreach ($row as $key => $value) {
           	  if($i>2 and $i<13)
              {
                $tmp[] = $value==1 ? 'V' : '';
                
                $arrjml['row1'][$key] = $this->fjml_ttl($arrjml,array('row1',$key),$value==1 ? 1 : 0,'');

                if($Kd_prosplvl==1 or $Kd_prosplvl==6){
                    $arrjml['row2'][$key] = $this->fjml_ttl($arrjml,array('row2',$key),$value==1 ? 1 : 0,'');
                }elseif($Kd_prosplvl==2 or $Kd_prosplvl==7)
                {
                    $arrjml['row3'][$key] = $this->fjml_ttl($arrjml,array('row3',$key),$value==1 ? 1 : 0,'');  
                }
                  $arrjml['row2'][$key] = $this->fjml_ttl($arrjml,array('row2',$key),0,'');
                  $arrjml['row3'][$key] = $this->fjml_ttl($arrjml,array('row3',$key),0,'');                	
                

              } else{
           	      if($key=='nama'){
           	        $tmp[] = $value==''  ? 'TIDAK ADA NAMA' : $value;
           	      }elseif($i<13){           	        
           	         $tmp[] = $value;
           	      }
           	    }
              
               $i++;
           	}

           	$data1 = $tb2->getData("$kd_wl kd_fam=$row[Kd_fam] and kd_mutasi IS NULL");
              if(!empty($data1))
              {
              	foreach ($data1 as $row1) {
                   $j=1;
                   foreach ($row1 as $key1 => $value1) {
                       	  	  if($j>2){
                                 $tmp[] = $value1==0 ? '' : $value1;
                                 $arrjml['row1'][$key1] = $this->fjml_ttl($arrjml,array('row1',$key1),$value1,'');
                                
                                 if($Kd_prosplvl==1 or $Kd_prosplvl==6){
                                     $arrjml['row2'][$key1] = $this->fjml_ttl($arrjml,array('row2',$key1),$value1,'');
                                 }elseif($Kd_prosplvl==2 or $Kd_prosplvl==7)
                                 {
                                     $arrjml['row3'][$key1] = $this->fjml_ttl($arrjml,array('row3',$key1),$value1,'');  
                                 }
                                   $arrjml['row2'][$key1] = $this->fjml_ttl($arrjml,array('row2',$key1),0,'');
                                   $arrjml['row3'][$key1] = $this->fjml_ttl($arrjml,array('row3',$key1),0,'');                	
                                 

                       	  	  } else{
                                 $tmp[] = $value1==1 ? 'V' : ''; 
                                 $arrjml['row1'][$key1] = $this->fjml_ttl($arrjml,array('row1',$key1),$value1==1 ? 1 : 0,'');

                                 if($Kd_prosplvl==1 or $Kd_prosplvl==6){
                                       $arrjml['row2'][$key1] = $this->fjml_ttl($arrjml,array('row2',$key1),$value1==1 ? 1 : 0,'');
                                 }elseif($Kd_prosplvl==2 or $Kd_prosplvl==7)
                                 {
                                       $arrjml['row3'][$key1] = $this->fjml_ttl($arrjml,array('row3',$key1),$value1==1 ? 1 : 0,'');  
                                 }
                                   $arrjml['row2'][$key1] = $this->fjml_ttl($arrjml,array('row2',$key1),0,'');
                                   $arrjml['row3'][$key1] = $this->fjml_ttl($arrjml,array('row3',$key1),0,'');                	
                                   	
                       	  	  }	
                              $j++;    	  	
                       	  	}    	  	
              	   
              	}
              }

            $data2 = $tb3->getData("$kd_wl Kd_fammbrtyp=2 and kd_fam=$row[Kd_fam] and kd_mutasi IS NULL");  
              
            if(!empty($data2))
              {
              	foreach ($data2 as $row2) {
                   $j=1;
                   foreach ($row2 as $key2 => $value2) {
                       	  	  if($key2=='nama'){
           	                         $tmp[] = $value2==''  ? 'TIDAK ADA NAMA' : $value2;
           	                         $arrjml['row1'][$key2]='';
           	                         $arrjml['row2'][$key2]='';
           	                         $arrjml['row3'][$key2]='';
           	                  }elseif($j>1 && $j<=6 )
           	                  {
                                 $tmp[] = $value2;
                                 $arrjml['row1'][$key2] = $this->fjml_ttl($arrjml,array('row1',$key2),$value2!='' ? 1 : 0,'');

                                 if($Kd_prosplvl==1 or $Kd_prosplvl==6){
                                        $arrjml['row2'][$key2] = $this->fjml_ttl($arrjml,array('row2',$key2),$value2!='' ? 1 : 0,'');
                                 }elseif($Kd_prosplvl==2 or $Kd_prosplvl==7)
                                 {
                                        $arrjml['row3'][$key2] = $this->fjml_ttl($arrjml,array('row3',$key2),$value2!='' ? 1 : 0,'');  
                                 }
                                   $arrjml['row2'][$key2] = $this->fjml_ttl($arrjml,array('row2',$key2),0,'');
                                   $arrjml['row3'][$key2] = $this->fjml_ttl($arrjml,array('row3',$key2),0,'');                	
                                 


           	                  } else
           	                  {
           	                     $tmp[] = $value2==1 ? 'V' : '';  
           	                     $arrjml['row1'][$key2] = $this->fjml_ttl($arrjml,array('row1',$key2),$value2==1 ? 1 : 0,'');

           	                     if($Kd_prosplvl==1 or $Kd_prosplvl==6){
                                     $arrjml['row2'][$key2] = $this->fjml_ttl($arrjml,array('row2',$key2),$value2==1 ? 1 : 0,'');
                                 }elseif($Kd_prosplvl==2 or $Kd_prosplvl==7)
                                 {
                                     $arrjml['row3'][$key2] = $this->fjml_ttl($arrjml,array('row3',$key2),$value2==1 ? 1 : 0,'');  
                                 }
                                   $arrjml['row2'][$key2] = $this->fjml_ttl($arrjml,array('row2',$key2),0,'');
                                   $arrjml['row3'][$key2] = $this->fjml_ttl($arrjml,array('row3',$key2),0,'');                	
                                  
           	                  } 	    
  	
                              $j++;    	  	
                       	  	}    	  	
              	   
              	}
              }else{
              	 for($j=1;$j<=11;$j++)
              	 {
              	 	$tmp[]='';
              	 }



              }


            $tmp_dt_tb[]=$tmp;
            $nombrs++;
           }
        }
        $footer_tb=array();
        $tmp_footer=array();

        foreach ($arrjml as $key=>$value) {
          foreach ($value as $key1 => $value1) {
          	$tmp_footer[$key][$key1]=  is_float($value1)  ? number_format($value1,0,',','.') : $value1;
          }
			     
		} 

		$footer_tb = $tmp_footer;

        return array('isi_tb'=>$tmp_dt_tb,'footer_tb'=>$footer_tb);
	}

function getdtmenu02_tab2($idkec,$iddesa,$iddusun,$idrt){
        
        $kd_wl=$this->getkdwl($idkec,$iddesa,$iddusun,$idrt,'','');
        
        $this->arrayks();
        
        $dt_indk_ks = new dt_indikator_ks;
        $dt = $dt_indk_ks->getdata('id_ind_ks>=6 and id_ind_ks<=36');  
        
        $ind_ks=array();
        if(!empty($dt))
        {
          foreach ($dt as $row) {
            $ind_ks[]=$row['id_ind_ks'];
          }
        }  
       
        $selct_txt='';        
        foreach($this->arr_ks as $key=>$value)
        {
          $selct_txt .= (!empty($selct_txt) ? ',':''). "if($value,1,0) as ks_$key";            
        }  


        $tb = new tb_gen('tbgen');
        $tb->sql_select="a.kd_fam,a.Kd_prosplvl,CONCAT('array(',GROUP_CONCAT(id_ind_ks,'=>','".'"'."',R_prosPinStat,'".'"'."'),')') AS array_ks_val,$selct_txt";
        $tb->sql_from= '((dbo_family a INNER JOIN dbo_fam_ind_detail b ON a.kd_fam=b.kd_fam) LEFT JOIN dbo_prosp_ind_stat c ON c.kd_prospinstat= b.kd_prospinstat)';
        $tb->sql_orderby = 'a.kd_fam';
        $tb->sql_groupby = 'a.kd_fam';
        $data = $tb->getData("$kd_wl");
        
        $tmp_dt_tb=array();
        $arrjml = array();
        $i=1;
        if(!empty($data))
        {
           foreach ($data as $row) {
             $tmp=array();
             $tmp[] = $i;
             $tmp[] = $row['kd_fam'];

             eval("\$array_ks_val = $row[array_ks_val];");               

             foreach ($ind_ks as $row1) {
               $tmp[] = isset($array_ks_val[$row1]) ? $array_ks_val[$row1] : '';               
               $arrjml['row2']['V'.$row1] = $this->fjml_ttl($arrjml,array('row2','V'.$row1),
                                                      isset($array_ks_val[$row1]) ? $array_ks_val[$row1]=='V ' : 0,'');
               $arrjml['row3']['X'.$row1] = $this->fjml_ttl($arrjml,array('row3','X'.$row1),
                                                      isset($array_ks_val[$row1]) ? $array_ks_val[$row1]=='X ' : 0,'');
               $arrjml['row4']['-'.$row1] = $this->fjml_ttl($arrjml,array('row4','-'.$row1),
                                                      isset($array_ks_val[$row1]) ? $array_ks_val[$row1]=='- ' : 0,'');
               $arrjml['row5']['X*'.$row1] = $this->fjml_ttl($arrjml,array('row5','X*'.$row1),
                                                      isset($array_ks_val[$row1]) ? $array_ks_val[$row1]=='X*' : 0,'');
               $arrjml['row6']['praks'.$row1] = $this->fjml_ttl($arrjml,array('row6','praks'.$row1),
                                                      isset($array_ks_val[$row1]) ? (($row['Kd_prosplvl']==1 or $row['Kd_prosplvl']==6) and ($array_ks_val[$row1]=='X ' or  $array_ks_val[$row1]=='X*')) : 0,'');
               $arrjml['row7']['ks'.$row1] = $this->fjml_ttl($arrjml,array('row7','ks'.$row1),
                                                      isset($array_ks_val[$row1]) ? (($row['Kd_prosplvl']==2 or $row['Kd_prosplvl']==7) and ($array_ks_val[$row1]=='X ' or  $array_ks_val[$row1]=='X*')) : 0,'');
             }

             foreach($this->arr_ks as $key=>$value)
             {
               $txt ="ks_$key";
               $tmp[] = $row[$txt] == 1 ? 'V' : '';
               $arrjml['row1'][$txt] = $this->fjml_ttl($arrjml,array('row1',$txt),$row[$txt] == 1 ? 1 : 0,'');             
             }

             $tmp_dt_tb[]=$tmp;
             $i++;
            
           }
        }

        $footer_tb=array();
        $tmp_footer=array();

        foreach ($arrjml as $key=>$value) {
          foreach ($value as $key1 => $value1) {
            $tmp_footer[$key][$key1]= number_format($value1,0,',','.');
          }
        } 

        $footer_tb = $tmp_footer;

        return array('isi_tb'=>$tmp_dt_tb,'footer_tb'=>$footer_tb);
  }


	function getdtmenu02_tab3($idkec,$iddesa,$iddusun,$idrt){
        
        $kd_wl=$this->getkdwl($idkec,$iddesa,$iddusun,$idrt,'idv','');
        
        $tb = new tb_gen('tbgen');
		$tb->sql_from= 'dbo_individu idv 
		                   LEFT JOIN dbo_edu_lvl edu ON idv.Kd_edu=edu.Kd_edu
                           LEFT JOIN dbo_empmnt_stat emp ON idv.Kd_emp=emp.Kd_emp
				           LEFT JOIN dbo_gender gen ON idv.Kd_gen=gen.Kd_gen
				           LEFT JOIN dbo_martl_stat ms ON idv.Kd_martl=ms.Kd_martl
				           LEFT JOIN dbo_mutasi mts ON idv.Kd_mutasi=mts.Kd_mutasi
				           LEFT JOIN dbo_fam_mbr_typ fmt ON idv.Kd_fammbrtyp=fmt.Kd_fammbrtyp';
        $tb->sql_orderby = 'idv.kd_fam,idv.Kd_mutasi,idv.Kd_fammbrtyp';
        $data = $tb->getData("$kd_wl");
        
        $tmp_dt_db=array();
        if(!empty($data))
        {
           foreach ($data as $row) {
           	$tgl=explode("-",$row['Tgl_lahir']);
           	$tmp_dt_db[$row['Kd_fam']]['jml'] = isset($tmp_dt_db[$row['Kd_fam']]) ? $tmp_dt_db[$row['Kd_fam']]['jml']+1 : 1; 
           	$tmp_dt_db[$row['Kd_fam']]['data'][]=array($row['Kd_fam'],
           		                                       $row['Kd_indv'],
           		                                       $row['Nama'],
           		                                       $row['Nm_fammbrtyp_ind'],
           		                                       $row['Nm_gen_ind'],
           		                                       $tgl[2]."/".$tgl[1]."/".$tgl[0],
           		                                       $row['Nm_emp_ind'],
           		                                       $row['Nm_edu_ind'],
           		                                       $row['Nm_martl_ind'],
           		                                       $row['Nm_mutasi']);
           }
        }

        return $tmp_dt_db;
	}

	function getdtmenu02_tab4($idkec,$iddesa,$iddusun,$idrt){
        
        $kd_wl=$this->getkdwl($idkec,$iddesa,$iddusun,$idrt);
        
        $tb = new tb_gen('tbgen');		
		$tb->sql_from= 'vw_fam_indv f';
		$tb->sql_select = "Kd_fam,Nama,
							(SELECT p.Nm_prosplvl_ind FROM dbo_prosp_lvl p WHERE f.Kd_prosplvl=p.Kd_prosplvl) AS prosp,
							(SELECT ii.Nama FROM dbo_individu ii WHERE f.Kd_fam=ii.Kd_fam AND ii.Kd_fammbrtyp=2 AND ii.Kd_mutasi IS NULL ORDER BY ii.Tgl_lahir LIMIT 0,1) AS istr,
							(SELECT ii.Kd_indv FROM dbo_individu ii WHERE f.Kd_fam=ii.Kd_fam AND ii.Kd_fammbrtyp=2 AND ii.Kd_mutasi IS NULL ORDER BY ii.Tgl_lahir LIMIT 0,1) AS id_istr,
							(SELECT DATE_FORMAT(FROM_DAYS(TO_DAYS(NOW())-TO_DAYS(Tgl_lahir)),'%Y')+0 FROM dbo_individu ii WHERE f.Kd_fam=ii.Kd_fam AND ii.Kd_fammbrtyp=2 AND ii.Kd_mutasi IS NULL ORDER BY ii.Tgl_lahir LIMIT 0,1) AS istr_u,
							(SELECT COUNT(*) FROM dbo_individu ii WHERE f.Kd_fam=ii.Kd_fam AND ii.Kd_fammbrtyp=3 AND ii.Kd_mutasi IS NULL) AS ank,
							(SELECT MIN(DATE_FORMAT(FROM_DAYS(TO_DAYS(NOW())-TO_DAYS(Tgl_lahir)),'%Y')+0) FROM dbo_individu ii WHERE f.Kd_fam=ii.Kd_fam AND ii.Kd_fammbrtyp=3 AND ii.Kd_mutasi IS NULL GROUP BY ii.Kd_fam) AS ank_kecil,
							(SELECT ii.Kd_indv FROM dbo_individu ii WHERE f.Kd_fam=ii.Kd_fam AND ii.Kd_fammbrtyp=3 AND ii.Kd_mutasi IS NULL ORDER BY ii.Tgl_lahir DESC LIMIT 0,1) AS id_ank_kecil ";
        $tb->sql_orderby = 'Kd_fam';
        $data = $tb->getData("$kd_wl Kd_contyp IS NOT NULL AND 
        	                         pus='1' AND 
        	                         Kd_martl=2 AND 
        	                         Kd_fammbrtyp=1 AND 
        	                         Kd_mutasi IS NULL AND 
        	                         (SELECT COUNT(*) AS j_istr FROM dbo_individu ii WHERE f.Kd_fam=ii.Kd_fam AND ii.Kd_fammbrtyp=2 AND ii.Kd_mutasi IS NULL HAVING j_istr > 0) ");
        
        $tmp_dt_db=array();
        if(!empty($data))
        {
           foreach ($data as $row) {
           	  $tmp = array(($row['istr']!='') ? $row['istr'] : 'TIDAK ADA NAMA',
           	  	           ($row['nama']!='')  ? $row['nama'] : 'TIDAK ADA NAMA',
           	  	            $row['istr_u'],($row['ank'] > 0) ? $row['ank'] : '-',
           	  	           (isset($row['ank_kecil'])) ? $row['ank_kecil'] : '-',
           	  	           $row['prosp']);
           	  $tmp_dt_db['data'][]=$tmp;
           }
        }

        return $tmp_dt_db;
	}

	function getdtmenu02_tab5($idkec,$iddesa,$iddusun,$idrt){
        
        $kd_wl=$this->getkdwl($idkec,$iddesa,$iddusun,$idrt);
        
        $tb = new tb_gen('tbgen');		
		$tb->sql_from= 'vw_fam_indv f';
		$tb->sql_select = "Kd_fam,Nama,
							(SELECT p.Nm_prosplvl_ind FROM dbo_prosp_lvl p WHERE f.Kd_prosplvl=p.Kd_prosplvl) AS prosp,
							(SELECT ii.Nama FROM dbo_individu ii WHERE f.Kd_fam=ii.Kd_fam AND ii.Kd_fammbrtyp=2 AND ii.Kd_mutasi IS NULL ORDER BY ii.Tgl_lahir LIMIT 0,1) AS istr,
							(SELECT ii.Kd_indv FROM dbo_individu ii WHERE f.Kd_fam=ii.Kd_fam AND ii.Kd_fammbrtyp=2 AND ii.Kd_mutasi IS NULL ORDER BY ii.Tgl_lahir LIMIT 0,1) AS id_istr,
							(SELECT DATE_FORMAT(FROM_DAYS(TO_DAYS(NOW())-TO_DAYS(Tgl_lahir)),'%Y')+0 FROM dbo_individu ii WHERE f.Kd_fam=ii.Kd_fam AND ii.Kd_fammbrtyp=2 AND ii.Kd_mutasi IS NULL ORDER BY ii.Tgl_lahir LIMIT 0,1) AS istr_u,
							(SELECT COUNT(*) FROM dbo_individu ii WHERE f.Kd_fam=ii.Kd_fam AND ii.Kd_fammbrtyp=3 AND ii.Kd_mutasi IS NULL) AS ank,
							(SELECT MIN(DATE_FORMAT(FROM_DAYS(TO_DAYS(NOW())-TO_DAYS(Tgl_lahir)),'%Y')+0) FROM dbo_individu ii WHERE f.Kd_fam=ii.Kd_fam AND ii.Kd_fammbrtyp=3 AND ii.Kd_mutasi IS NULL GROUP BY ii.Kd_fam) AS ank_kecil,
							(SELECT ii.Kd_indv FROM dbo_individu ii WHERE f.Kd_fam=ii.Kd_fam AND ii.Kd_fammbrtyp=3 AND ii.Kd_mutasi IS NULL ORDER BY ii.Tgl_lahir DESC LIMIT 0,1) AS id_ank_kecil ";
        $tb->sql_orderby = 'Kd_fam';
        $data = $tb->getData("$kd_wl (Kd_prosplvl=1 OR Kd_prosplvl=2 OR Kd_prosplvl=6 OR Kd_prosplvl=7) AND 
        	                          Kd_contyp IS NOT NULL AND 
        	                          pus='1' AND 
        	                          Kd_martl=2 AND Kd_fammbrtyp=1 AND Kd_mutasi IS NULL AND 
        	                          (SELECT COUNT(*) AS j_istr FROM dbo_individu ii WHERE f.Kd_fam=ii.Kd_fam AND ii.Kd_fammbrtyp=2 AND ii.Kd_mutasi IS NULL HAVING j_istr > 0)");
        
        $tmp_dt_db=array();
        if(!empty($data))
        {
           foreach ($data as $row) {
           	  $tmp = array(($row['istr']!='') ? $row['istr'] : 'TIDAK ADA NAMA',
           	  	           ($row['nama']!='')  ? $row['nama'] : 'TIDAK ADA NAMA',
           	  	            $row['istr_u'],($row['ank'] > 0) ? $row['ank'] : '-',
           	  	           (isset($row['ank_kecil'])) ? $row['ank_kecil'] : '-',
           	  	           $row['prosp']);
           	  $tmp_dt_db['data'][]=$tmp;
           }
        }

        return $tmp_dt_db;
	}


  function getdtmenu03_tab1($idkec,$iddesa,$iddusun,$idrt){
    
    $kd_wl=$this->getkdwl($idkec,$iddesa,$iddusun,$idrt,'','','id_unit_detail_idk');

    $u1549 = $this->getrentang(15,49);
    
    $dt = new dt_unit_detail;              
    $data = $dt->getdata("$kd_wl");

    $this->arrayks();

    $tb = new tb_gen('tbgen');
    $tb->sql_from="vw_fam_indv";
    $tb->sql_select = "SUM( Kd_fammbrtyp=1) AS j_rt,".
                          "SUM( Kd_fammbrtyp=1 AND  Kd_gen=1) AS j_lk_kk,".
                  "SUM( Kd_fammbrtyp=1 AND  Kd_gen=2) AS j_pr_kk,".
                  "SUM( Kd_fammbrtyp=1 AND  Kd_emp!=6) AS j_krj_kk,".
                  "SUM( Kd_fammbrtyp=1 AND  Kd_emp=6) AS j_tkrj_kk,".
                  "SUM( Kd_fammbrtyp=1 AND  Kd_martl=2) AS j_kwn_kk,".
                  "SUM( Kd_fammbrtyp=1 AND  Kd_martl!=2) AS j_tkwn_kk,".
                  "SUM( Kd_fammbrtyp=1 AND  Kd_edu=2) AS j_ttmt_sd_kk,".
                  "SUM( Kd_fammbrtyp=1 AND ( Kd_edu=3 OR  Kd_edu=5)) AS j_tmt_sd_sltp_kk,".
                  "SUM( Kd_fammbrtyp=1 AND  Kd_edu=7) AS j_tmt_slta_kk,".
                  "SUM( Kd_fammbrtyp=1 AND  Kd_edu=9) AS j_tmt_ak_pt_kk,".
                  "SUM( Bantuan_modal='1' AND  Kd_fammbrtyp=1) AS j_btm_kk,".
                  "SUM( Bantuan_modal='0' AND  Kd_fammbrtyp=1) AS j_tbtm_kk,".
                  "SUM( Kd_gen=1) AS j_lk_jiwa,".
                  "SUM( Kd_gen=2) AS j_pr_jiwa,".
                  "SUM( Kd_gen=2 AND ($u1549)) AS j_wus,".
                  "SUM((".$this->arr_ks['pra_s'].") AND  Kd_fammbrtyp=1) AS pra_s_j_rt,".
                  "SUM((".$this->arr_ks['pra_s'].") AND  Kd_fammbrtyp=1 AND  Kd_gen=1) AS pra_s_j_lk_kk,".
                  "SUM((".$this->arr_ks['pra_s'].") AND  Kd_fammbrtyp=1 AND  Kd_gen=2) AS pra_s_j_pr_kk,".
                  "SUM((".$this->arr_ks['pra_s'].") AND  Kd_fammbrtyp=1 AND  Kd_emp!=6) AS pra_s_j_krj_kk,".
                  "SUM((".$this->arr_ks['pra_s'].") AND  Kd_fammbrtyp=1 AND  Kd_emp=6) AS pra_s_j_tkrj_kk,".
                  "SUM((".$this->arr_ks['pra_s'].") AND  Kd_fammbrtyp=1 AND  Kd_martl=2) AS pra_s_j_kwn_kk,".
                  "SUM((".$this->arr_ks['pra_s'].") AND  Kd_fammbrtyp=1 AND  Kd_martl!=2) AS pra_s_j_tkwn_kk,".
                  "SUM((".$this->arr_ks['pra_s'].") AND  Kd_fammbrtyp=1 AND  Kd_edu=2) AS pra_s_j_ttmt_sd_kk,".
                  "SUM((".$this->arr_ks['pra_s'].") AND  Kd_fammbrtyp=1 AND ( Kd_edu=3 OR  Kd_edu=5)) AS pra_s_j_tmt_sd_sltp_kk,".
                  "SUM((".$this->arr_ks['pra_s'].") AND  Kd_fammbrtyp=1 AND  Kd_edu=7) AS pra_s_j_tmt_slta_kk,".
                  "SUM((".$this->arr_ks['pra_s'].") AND  Kd_fammbrtyp=1 AND  Kd_edu=9) AS pra_s_j_tmt_ak_pt_kk,".
                  "SUM((".$this->arr_ks['pra_s'].") AND  Bantuan_modal='1' AND  Kd_fammbrtyp=1) AS pra_s_j_btm_kk,".
                  "SUM((".$this->arr_ks['pra_s'].") AND  Bantuan_modal='0' AND  Kd_fammbrtyp=1) AS pra_s_j_tbtm_kk,".
                  "SUM((".$this->arr_ks['pra_s'].") AND  Kd_gen=1) AS pra_s_j_lk_jiwa,".
                  "SUM((".$this->arr_ks['pra_s'].") AND  Kd_gen=2) AS pra_s_j_pr_jiwa,".
                  "SUM((".$this->arr_ks['pra_s'].") AND  Kd_gen=2 AND ($u1549)) AS pra_s_j_wus,".
                  "SUM((".$this->arr_ks['ks_1'].") AND  Kd_fammbrtyp=1) AS ks_j_rt,".
                  "SUM((".$this->arr_ks['ks_1'].") AND  Kd_fammbrtyp=1 AND  Kd_gen=1) AS ks_j_lk_kk,".
                  "SUM((".$this->arr_ks['ks_1'].") AND  Kd_fammbrtyp=1 AND  Kd_gen=2) AS ks_j_pr_kk,".
                  "SUM((".$this->arr_ks['ks_1'].") AND  Kd_fammbrtyp=1 AND  Kd_emp!=6) AS ks_j_krj_kk,".
                  "SUM((".$this->arr_ks['ks_1'].") AND  Kd_fammbrtyp=1 AND  Kd_emp=6) AS ks_j_tkrj_kk,".
                  "SUM((".$this->arr_ks['ks_1'].") AND  Kd_fammbrtyp=1 AND  Kd_martl=2) AS ks_j_kwn_kk,".
                  "SUM((".$this->arr_ks['ks_1'].") AND  Kd_fammbrtyp=1 AND  Kd_martl!=2) AS ks_j_tkwn_kk,".
                  "SUM((".$this->arr_ks['ks_1'].") AND  Kd_fammbrtyp=1 AND  Kd_edu=2) AS ks_j_ttmt_sd_kk,".
                  "SUM((".$this->arr_ks['ks_1'].") AND  Kd_fammbrtyp=1 AND ( Kd_edu=3 OR  Kd_edu=5)) AS ks_j_tmt_sd_sltp_kk,".
                  "SUM((".$this->arr_ks['ks_1'].") AND  Kd_fammbrtyp=1 AND  Kd_edu=7) AS ks_j_tmt_slta_kk,".
                  "SUM((".$this->arr_ks['ks_1'].") AND  Kd_fammbrtyp=1 AND  Kd_edu=9) AS ks_j_tmt_ak_pt_kk,".
                  "SUM((".$this->arr_ks['ks_1'].") AND  Bantuan_modal='1' AND  Kd_fammbrtyp=1) AS ks_j_btm_kk,".
                  "SUM((".$this->arr_ks['ks_1'].") AND  Bantuan_modal='0' AND  Kd_fammbrtyp=1) AS ks_j_tbtm_kk,".
                  "SUM((".$this->arr_ks['ks_1'].") AND  Kd_gen=1) AS ks_j_lk_jiwa,".
                  "SUM((".$this->arr_ks['ks_1'].") AND  Kd_gen=2) AS ks_j_pr_jiwa,".
                  "SUM((".$this->arr_ks['ks_1'].") AND  Kd_gen=2 AND ($u1549)) AS ks_j_wus ";

    $dt_tb=array();
    $arrjml = array();
    $i=1;
    foreach($data as $row)
    {
      $tmp_dt_tb=array();
      $tmp_dt_tb[]=$i;
      $tmp_dt_tb[]=$row['no_unit_detail'];
      
      if($idkec==0){
         $jml=$dt->getjml($row['id_unit_detail'],12);
         $tmp_dt_tb[]=number_format($jml,0,',','.');
         $arrjml['row1']['jml1'] = $this->fjml_ttl($arrjml,array('row1','jml1'),$jml,'');
         $tmp_dt_tb[]=number_format($jml,0,',','.');
         $arrjml['row1']['jml2'] = $this->fjml_ttl($arrjml,array('row1','jml2'),'',$jml,'');
      }
      
      if($iddesa==0){         
         $jml=$dt->getjml($row['id_unit_detail'],13);
         $tmp_dt_tb[]=number_format($jml,0,',','.');
         $arrjml['row1']['jml3'] = $this->fjml_ttl($arrjml,array('row1','jml3'),$jml,'');
         $tmp_dt_tb[]=number_format($jml,0,',','.');
         $arrjml['row1']['jml4'] = $this->fjml_ttl($arrjml,array('row1','jml4'),$jml,'');
      }

      if($iddusun==0)
      {
         $jml=$dt->getjml($row['id_unit_detail'],14);
         $tmp_dt_tb[]=number_format($jml,0,',','.');
         $arrjml['row1']['jml5'] = $this->fjml_ttl($arrjml,array('row1','jml5'),$jml,'');
         $tmp_dt_tb[]=number_format($jml,0,',','.');
         $arrjml['row1']['jml6'] = $this->fjml_ttl($arrjml,array('row1','jml6'),$jml,'');
      }

      $kd_wlq=$this->getkdwl(($idkec==0 ? $row['id_unit_detail'] : $idkec ),
      ((($idkec!=0) and ($iddesa == 0)) ? $row['id_unit_detail'] : $iddesa),
      ((($idkec!=0) and ($iddesa != 0) and ($iddusun==0)) ? $row['id_unit_detail']  : $iddusun),
      ((($idkec!=0) and ($iddesa != 0) and ($iddusun!=0) and ($idrt==0)) ? $row['id_unit_detail']  : $idrt));  

      $data1 = $tb->getData("$kd_wlq Kd_mutasi IS NULL");
      $rc = $this->build_rc($data1);

      $tmp_dt_tb[]=$this->frupiah($rc,'j_rt');
      $arrjml['row1']['jml7'] = $this->fjml_ttl($arrjml,array('row1','jml7'),$rc,'j_rt');
      $tmp_dt_tb[]=$this->frupiah($rc,'j_rt');
      $arrjml['row1']['jml8'] = $this->fjml_ttl($arrjml,array('row1','jml8'),$rc,'j_rt');
      $tmp_dt_tb[]=$this->frupiah($rc,'j_rt');
      $arrjml['row1']['jml9'] = $this->fjml_ttl($arrjml,array('row1','jml9'),$rc,'j_rt');
      $tmp_dt_tb[]=$this->frupiah($rc,'j_rt');
      $arrjml['row1']['jml10'] = $this->fjml_ttl($arrjml,array('row1','jml10'),$rc,'j_rt');
      $arrjml['row2']['jml10'] = $this->fjml_ttl($arrjml,array('row2','jml10'),$rc,'pra_s_j_rt');
      $arrjml['row3']['jml10'] = $this->fjml_ttl($arrjml,array('row3','jml10'),$rc,'ks_j_rt');

      $j=1;
      if(!empty($rc)){  
        foreach ($rc as $key => $value) {
          if($j>1 and $j<=15){
            $tmp_dt_tb[]=number_format($value,0,',','.'); 
            $arrjml['row1'][$key] = $this->fjml_ttl($arrjml,array('row1',$key),$value,'');
          }

          if($j>16 and $j<=30){            
            $arrjml['row2'][$key] = $this->fjml_ttl($arrjml,array('row2',$key),$value,'');
          }

          if($j>31 and $j<=45){             
            $arrjml['row3'][$key] = $this->fjml_ttl($arrjml,array('row3',$key),$value,'');
          }

          $j++;
        }
        $tmp_dt_tb[]=number_format($rc['j_lk_jiwa']+$rc['j_pr_jiwa'],0,',','.');
        $arrjml['row1']['jml11'] = $this->fjml_ttl($arrjml,array('row1','jml11'),$rc['j_lk_jiwa']+$rc['j_pr_jiwa'],'');
        $tmp_dt_tb[]=number_format($rc['j_wus'],0,',','.');
        $arrjml['row1']['jml12'] = $this->fjml_ttl($arrjml,array('row1','jml12'),$rc,'j_wus');

        $arrjml['row2']['jml11'] = $this->fjml_ttl($arrjml,array('row2','jml11'),$rc['pra_s_j_lk_jiwa']+$rc['pra_s_j_pr_jiwa'],'');
        $arrjml['row2']['jml12'] = $this->fjml_ttl($arrjml,array('row2','jml12'),$rc,'pra_s_j_wus'); 

        $arrjml['row3']['jml11'] = $this->fjml_ttl($arrjml,array('row3','jml11'),$rc['ks_j_lk_jiwa']+$rc['ks_j_pr_jiwa'],'');
        $arrjml['row3']['jml12'] = $this->fjml_ttl($arrjml,array('row3','jml12'),$rc,'ks_j_wus'); 

      }else{
          for($j=1;$j<17;$j++)
          {
            $tmp_dt_tb[]=0;
          }
          
        }
      


      $dt_tb[] = $tmp_dt_tb;
      $i++;
    } 

       
    $footer_tb=array();
        $tmp_footer=array();

        foreach ($arrjml as $key=>$value) {
          foreach ($value as $key1 => $value1) {
            $tmp_footer[$key][$key1]= number_format($value1,0,',','.');
          }
        } 

        $footer_tb = $tmp_footer;


    return array('isi_tb'=>$dt_tb,'footer_tb'=>$footer_tb);

  }  

  function getdtmenu03_tab2($idkec,$iddesa,$iddusun,$idrt){

    $kd_wl=$this->getkdwl($idkec,$iddesa,$iddusun,$idrt,'','','id_unit_detail_idk');    
    
    $dt = new dt_unit_detail;              
    $data = $dt->getdata("$kd_wl");

    $this->arrayks();
        
        $u01 = $this->getrentang(0,1);
        $u15 = $this->getrentang(1,4);
        $u56 = $this->getrentang(5,6);
        $u715 = $this->getrentang(7,15);
        
        $u1621 = $this->getrentang(16,21);
        $u2259 = $this->getrentang(22,59);
        $u60 = $this->getrentang(60);

        $u020 = $this->getrentang(0,20);
        $u2029 = $this->getrentang(20,29);
        $u3049 = $this->getrentang(30,49);

        $tmp_dt = new dt_non_acptr_reas;
        $tmp_data = $tmp_dt->getdata('');
        
        $str_reas = '';
        $str_reas_pra_s = '';
        $str_reas_ks = '';

        if(!empty($tmp_data))
        {
          foreach ($tmp_data as $rc_reas) {         
            $str_reas.= (!empty($str_reas) ? ',' : '')."SUM(Kd_nonacptr=".$rc_reas['Kd_nonacptr']." AND Kd_fammbrtyp=1) AS j_reas_".$rc_reas['Kd_nonacptr'];
            $str_reas_pra_s.= (!empty($str_reas_pra_s) ? ',' : '')."SUM(((".$this->arr_ks['pra_s'].") AND Kd_nonacptr=".$rc_reas['Kd_nonacptr'].") AND Kd_fammbrtyp=1) AS pra_s_j_reas_".$rc_reas['Kd_nonacptr'];
            $str_reas_ks.= (!empty($str_reas_ks) ? ',' : '')."SUM(((".$this->arr_ks['ks_1'].") AND Kd_nonacptr=".$rc_reas['Kd_nonacptr'].") AND Kd_fammbrtyp=1) AS ks_j_reas_".$rc_reas['Kd_nonacptr'];
          } 
        }

    $tb = new tb_gen('tbgen');
    $tb->sql_from="vw_fam_indv";
    $tb->sql_select = "SUM(($u01) AND  Posyandu='1') AS j_blt_0_1_pos,".
                      "SUM(($u01) AND  Posyandu='0') AS j_blt_0_1_tpos,".
                      "SUM(($u15) AND  Posyandu='1') AS j_blt_1_5_pos,".
                      "SUM(($u15) AND  Posyandu='0') AS j_blt_1_5_tpos,".
                      "SUM($u56) AS j_5_6_th,".                                   
                      "SUM(($u715) AND  Kd_edu!=0 AND  Kd_gen=1) AS j_lk_sklh_7_15,".
                      "SUM(($u715) AND  Kd_edu!=0 AND  Kd_gen=2) AS j_pr_sklh_7_15,".
                      "SUM(($u715) AND  Kd_edu=0 AND  Kd_gen=1) AS j_lk_tsklh_7_15,".
                      "SUM(($u715) AND  Kd_edu=0 AND  Kd_gen=2) AS j_pr_tsklh_7_15,".
                      "SUM($u1621) AS j_16_21_th,".
                      "SUM($u2259) AS j_22_59_th,".
                      "SUM($u60) AS j_60_th,".
                      "SUM( pus='1' AND  Kd_fammbrtyp=1) AS j_pus,".
                      "SUM( pus='1' AND  Kd_fammbrtyp=2 AND ($u020)) AS j_20_th_pus,".
                      "SUM( pus='1' AND  Kd_fammbrtyp=2 AND ($u2029)) AS j_20_29_th_pus,".
                      "SUM( pus='1' AND  Kd_fammbrtyp=2 AND ($u3049)) AS j_30_49_th_pus,".
                      "SUM( Kd_consrc=1 AND  Kd_fammbrtyp=1) AS j_pmt_kb,".
                      "SUM( Kd_consrc=2 AND  Kd_fammbrtyp=1) AS j_swst_kb,".
                      "SUM(( Kd_implan=0 AND  Kd_implan IS NOT NULL AND  Kd_contyp=4 AND  Kd_consrc IS NOT NULL AND  Kd_consrc!=0) AND  Kd_fammbrtyp=1) AS j_impl,".
                      $str_reas.",".
                      "SUM((".$this->arr_ks['pra_s'].") AND ($u01) AND  Posyandu='1') AS pra_s_j_blt_0_1_pos,".
                      "SUM((".$this->arr_ks['pra_s'].") AND ($u01) AND  Posyandu='0') AS pra_s_j_blt_0_1_tpos,".
                      "SUM((".$this->arr_ks['pra_s'].") AND ($u15) AND  Posyandu='1') AS pra_s_j_blt_1_5_pos,".
                      "SUM((".$this->arr_ks['pra_s'].") AND ($u15) AND  Posyandu='0') AS pra_s_j_blt_1_5_tpos,".
                      "SUM((".$this->arr_ks['pra_s'].") AND ($u56)) AS pra_s_j_5_6_th,".                                    
                      "SUM((".$this->arr_ks['pra_s'].") AND ($u715) AND  Kd_edu!=0 AND  Kd_gen=1) AS pra_s_j_lk_sklh_7_15,".
                      "SUM((".$this->arr_ks['pra_s'].") AND ($u715) AND  Kd_edu!=0 AND  Kd_gen=2) AS pra_s_j_pr_sklh_7_15,".
                      "SUM((".$this->arr_ks['pra_s'].") AND ($u715) AND  Kd_edu=0 AND  Kd_gen=1) AS pra_s_j_lk_tsklh_7_15,".
                      "SUM((".$this->arr_ks['pra_s'].") AND ($u715) AND  Kd_edu=0 AND  Kd_gen=2) AS pra_s_j_pr_tsklh_7_15,".
                      "SUM((".$this->arr_ks['pra_s'].") AND ($u1621)) AS pra_s_j_16_21_th,".
                      "SUM((".$this->arr_ks['pra_s'].") AND ($u2259)) AS pra_s_j_22_59_th,".
                      "SUM((".$this->arr_ks['pra_s'].") AND ($u60)) AS pra_s_j_60_th,".
                      "SUM((".$this->arr_ks['pra_s'].") AND  pus='1' AND  Kd_fammbrtyp=1) AS pra_s_j_pus,".
                      "SUM((".$this->arr_ks['pra_s'].") AND  pus='1' AND  Kd_fammbrtyp=2 AND ($u020)) AS pra_s_j_20_th_pus,".
                      "SUM((".$this->arr_ks['pra_s'].") AND  pus='1' AND  Kd_fammbrtyp=2 AND ($u2029)) AS pra_s_j_20_29_th_pus,".
                      "SUM((".$this->arr_ks['pra_s'].") AND  pus='1' AND  Kd_fammbrtyp=2 AND ($u3049)) AS pra_s_j_30_49_th_pus,".
                      "SUM((".$this->arr_ks['pra_s'].") AND  Kd_consrc=1 AND  Kd_fammbrtyp=1) AS pra_s_j_pmt_kb,".
                      "SUM((".$this->arr_ks['pra_s'].") AND  Kd_consrc=2 AND  Kd_fammbrtyp=1) AS pra_s_j_swst_kb,".
                      "SUM((".$this->arr_ks['pra_s'].") AND ( Kd_implan=0 AND  Kd_implan IS NOT NULL AND  Kd_contyp=4 AND  Kd_consrc IS NOT NULL AND  Kd_consrc!=0 AND  Kd_fammbrtyp=1)) AS pra_s_j_impl,".
                      $str_reas_pra_s.",".
                      "SUM((".$this->arr_ks['ks_1'].") AND ($u01) AND  Posyandu='1') AS ks_j_blt_0_1_pos,".
                      "SUM((".$this->arr_ks['ks_1'].") AND ($u01) AND  Posyandu='0') AS ks_j_blt_0_1_tpos,".
                      "SUM((".$this->arr_ks['ks_1'].") AND ($u15) AND  Posyandu='1') AS ks_j_blt_1_5_pos,".
                      "SUM((".$this->arr_ks['ks_1'].") AND ($u15) AND  Posyandu='0') AS ks_j_blt_1_5_tpos,".
                      "SUM((".$this->arr_ks['ks_1'].") AND ($u56)) AS ks_j_5_6_th,".                                   
                      "SUM((".$this->arr_ks['ks_1'].") AND ($u715) AND  Kd_edu!=0 AND  Kd_gen=1) AS ks_j_lk_sklh_7_15,".
                      "SUM((".$this->arr_ks['ks_1'].") AND ($u715) AND  Kd_edu!=0 AND  Kd_gen=2) AS ks_j_pr_sklh_7_15,".
                      "SUM((".$this->arr_ks['ks_1'].") AND ($u715) AND  Kd_edu=0 AND  Kd_gen=1) AS ks_j_lk_tsklh_7_15,".
                      "SUM((".$this->arr_ks['ks_1'].") AND ($u715) AND  Kd_edu=0 AND  Kd_gen=2) AS ks_j_pr_tsklh_7_15,".
                      "SUM((".$this->arr_ks['ks_1'].") AND ($u1621)) AS ks_j_16_21_th,".
                      "SUM((".$this->arr_ks['ks_1'].") AND ($u2259)) AS ks_j_22_59_th,".
                      "SUM((".$this->arr_ks['ks_1'].") AND ($u60)) AS ks_j_60_th,".
                      "SUM((".$this->arr_ks['ks_1'].") AND  pus='1' AND  Kd_fammbrtyp=1) AS ks_j_pus,".
                      "SUM((".$this->arr_ks['ks_1'].") AND  pus='1' AND  Kd_fammbrtyp=2 AND ($u020)) AS ks_j_20_th_pus,".
                      "SUM((".$this->arr_ks['ks_1'].") AND  pus='1' AND  Kd_fammbrtyp=2 AND ($u2029)) AS ks_j_20_29_th_pus,".
                      "SUM((".$this->arr_ks['ks_1'].") AND  pus='1' AND  Kd_fammbrtyp=2 AND ($u3049)) AS ks_j_30_49_th_pus,".
                      "SUM((".$this->arr_ks['ks_1'].") AND  Kd_consrc=1 AND  Kd_fammbrtyp=1) AS ks_j_pmt_kb,".
                      "SUM((".$this->arr_ks['ks_1'].") AND  Kd_consrc=2 AND  Kd_fammbrtyp=1) AS ks_j_swst_kb,".
                      "SUM((".$this->arr_ks['ks_1'].") AND ( Kd_implan=0 AND  Kd_implan IS NOT NULL AND  Kd_contyp=4 AND  Kd_consrc IS NOT NULL AND  Kd_consrc!=0 AND  Kd_fammbrtyp=1)) AS ks_j_impl,".
                      $str_reas_ks.",".
                      "SUM((".$this->arr_ks['pra_s'].") AND  Kd_fammbrtyp=1) AS j_pra_s,".
                      "SUM((".$this->arr_ks['ks_1'].") AND  Kd_fammbrtyp=1) AS j_ks_1,".
                      "SUM(".$this->arr_ks['ks_2']." AND  Kd_fammbrtyp=1) AS j_ks_2,".
                      "SUM(".$this->arr_ks['ks_3']." AND  Kd_fammbrtyp=1) AS j_ks_3,".
                      "SUM(".$this->arr_ks['ks_3_p']." AND  Kd_fammbrtyp=1) AS j_ks_3_p";

    $dt_tb=array();
    $arrjml = array();
    $i=1;
    foreach($data as $row)
    {
      $tmp_dt_tb=array();
      //$tmp_dt_tb[]=$i;
      //$tmp_dt_tb[]=$row['no_unit_detail'];
      
      $kd_wlq=$this->getkdwl(($idkec==0 ? $row['id_unit_detail'] : $idkec ),
      ((($idkec!=0) and ($iddesa == 0)) ? $row['id_unit_detail'] : $iddesa),
      ((($idkec!=0) and ($iddesa != 0) and ($iddusun==0)) ? $row['id_unit_detail']  : $iddusun),
      ((($idkec!=0) and ($iddesa != 0) and ($iddusun!=0) and ($idrt==0)) ? $row['id_unit_detail']  : $idrt));  

      $data1 = $tb->getData("$kd_wlq Kd_mutasi IS NULL");
      $rc = $this->build_rc($data1);

      
      $j=1;
      if(!empty($rc)){  
        foreach ($rc as $key => $value) {
          if($j<=23){
            $tmp_dt_tb[]=number_format($value,0,',','.'); 
            $arrjml['row1'][$key] = $this->fjml_ttl($arrjml,array('row1',$key),$value,'');
          }

          if($j>23 and $j<=46){            
            $arrjml['row2'][$key] = $this->fjml_ttl($arrjml,array('row2',$key),$value,'');
          }

          if($j>46 and $j<=69){             
            $arrjml['row3'][$key] = $this->fjml_ttl($arrjml,array('row3',$key),$value,'');
            $jml=0;
          }

          if($j>69){
            $tmp_dt_tb[]=number_format($value,0,',','.');
            $jml=$jml+$value; 
            $arrjml['row1'][$key] = $this->fjml_ttl($arrjml,array('row1',$key),$value,'');
          }

          $j++;
        }

        $tmp_dt_tb[]=number_format($jml,0,',','.');
        $arrjml['row1']['jml'] = $this->fjml_ttl($arrjml,array('row1','jml'),$jml,'');
        
      }else{
          for($j=1;$j<30;$j++)
          {
            $tmp_dt_tb[]=0;
          }
          
        }
      


      $dt_tb[] = $tmp_dt_tb;
      $i++;
    } 

       
    $footer_tb=array();
        $tmp_footer=array();

        foreach ($arrjml as $key=>$value) {
          foreach ($value as $key1 => $value1) {
            $tmp_footer[$key][$key1]= number_format($value1,0,',','.');
          }
        } 

        $footer_tb = $tmp_footer;

    return array('isi_tb'=>$dt_tb,'footer_tb'=>$footer_tb);

  }  

  function getdtmenu03_tab3($idkec,$iddesa,$iddusun,$idrt){

    $kd_wl=$this->getkdwl($idkec,$iddesa,$iddusun,$idrt,'','','id_unit_detail_idk');    
    
    $dt = new dt_unit_detail;              
    $data = $dt->getdata("$kd_wl");

    $this->arrayks();
                
        $tmp_dt = new dt_contr_typ;
        $tmp_data = $tmp_dt->getdata('');

        $str_qr_idk = '';
        $pra_s_str_qr_idk = '';
        $ks_str_qr_idk = '';

        if(!empty($tmp_data))
        {
          foreach ($tmp_data as $rc_typ) {         
            $str_qr_idk.= (!empty($str_qr_idk) ? ',' : '')."SUM(Kd_contyp=$rc_typ[Kd_contyp]) AS j_typ_$rc_typ[Kd_contyp]";
            $pra_s_str_qr_idk.= (!empty($pra_s_str_qr_idk) ? ',' : '')."SUM((".$this->arr_ks['pra_s'].") AND Kd_contyp=$rc_typ[Kd_contyp]) AS pra_s_j_typ_$rc_typ[Kd_contyp]";
            $ks_str_qr_idk.= (!empty($ks_str_qr_idk) ? ',' : '')."SUM((".$this->arr_ks['ks_1'].") AND Kd_contyp=$rc_typ[Kd_contyp]) AS ks_j_typ_$rc_typ[Kd_contyp]";
          } 
        }

    $tb = new tb_gen('dbo_family');
    //$tb->sql_from="vw_fam_indv";
    $tb->sql_select = "COUNT(*) AS jd,
                       $str_qr_idk,
                       SUM(".$this->arr_ks['pra_s'].") pra_s_j_pus,
                       $pra_s_str_qr_idk,
                       SUM(".$this->arr_ks['ks_1'].") ks_j_pus,                       
                       $ks_str_qr_idk";

    $dt_tb=array();
    $arrjml = array();
    $i=1;
    foreach($data as $row)
    {
      $tmp_dt_tb=array();
      $tmp_dt_tb[]=$i;
      $tmp_dt_tb[]=$row['no_unit_detail'];
      
      $kd_wlq=$this->getkdwl(($idkec==0 ? $row['id_unit_detail'] : $idkec ),
      ((($idkec!=0) and ($iddesa == 0)) ? $row['id_unit_detail'] : $iddesa),
      ((($idkec!=0) and ($iddesa != 0) and ($iddusun==0)) ? $row['id_unit_detail']  : $iddusun),
      ((($idkec!=0) and ($iddesa != 0) and ($iddusun!=0) and ($idrt==0)) ? $row['id_unit_detail']  : $idrt));  

      $data1 = $tb->getData("$kd_wlq pus='1'");
      $rc = $this->build_rc($data1);

      
      $j=1;
      $jml=0;
      $jml1=0;
      $jml2=0;
      if(!empty($rc)){  
        foreach ($rc as $key => $value) {
          if($j<=9){
            $tmp_dt_tb[]=number_format($value,0,',','.'); 
            if($j>1){ 
              $jml=$jml+$value;
            }

            $arrjml['row1'][$key] = $this->fjml_ttl($arrjml,array('row1',$key),$value,'');
          }

          if($j>9 and $j<=18){
            if($j>10){ 
              $jml1=$jml1+$value;
            }            
            $arrjml['row2'][$key] = $this->fjml_ttl($arrjml,array('row2',$key),$value,'');
          }

          if($j>18 and $j<=32){ 
          if($j>19){ 
              $jml2=$jml2+$value;
            }               
            $arrjml['row3'][$key] = $this->fjml_ttl($arrjml,array('row3',$key),$value,'');            
          }
          
          $j++;
        }

        $tmp_dt_tb[]=number_format($jml,0,',','.');
        $tmp_dt_tb[]=number_format($this->fprosen($jml,'',$rc,'jd'),2,',','.').'%';
        $arrjml['row1']['jml'] = $this->fjml_ttl($arrjml,array('row1','jml'),$jml,''); 
        $arrjml['row1']['prosen'] =  $this->fprosen($arrjml,array('row1','jml'),$arrjml,array('row1','jd')) ;
        $arrjml['row2']['jml1'] = $this->fjml_ttl($arrjml,array('row2','jml1'),$jml1,'');
        $arrjml['row2']['prosen'] =  $this->fprosen($arrjml,array('row2','jml1'),$arrjml,array('row2','pra_s_j_pus')) ;
        $arrjml['row3']['jml2'] = $this->fjml_ttl($arrjml,array('row3','jml2'),$jml2,'');
        $arrjml['row3']['prosen'] =  $this->fprosen($arrjml,array('row3','jml2'),$arrjml,array('row3','ks_j_pus')) ;
      }else{
          for($j=1;$j<11;$j++)
          {
            $tmp_dt_tb[]=0;
          }
          $tmp_dt_tb[]='0%';
        }

      $dt_tb[] = $tmp_dt_tb;
      $i++;
    } 

       
    $footer_tb=array();
        $tmp_footer=array();

        foreach ($arrjml as $key=>$value) {
          foreach ($value as $key1 => $value1) {
            if($key1!='prosen'){ 
             $tmp_footer[$key][$key1]= number_format($value1,0,',','.');
            }else{
             $tmp_footer[$key][$key1]= number_format($value1,2,',','.').'%';
            } 
          }
        } 

        $footer_tb = $tmp_footer;
    return array('isi_tb'=>$dt_tb,'footer_tb'=>$footer_tb);

  }

  function getdtmenu03_tab4($idkec,$iddesa,$iddusun,$idrt){

    $kd_wl=$this->getkdwl($idkec,$iddesa,$iddusun,$idrt,'','','id_unit_detail_idk');    

    
    $dt = new dt_unit_detail;              
    $data = $dt->getdata("$kd_wl");

    $this->arrayks();
                
        $tmp_dt = new dt_contr_typ;
        $tmp_data = $tmp_dt->getdata('');

        $str_qr_idk = '';
        $pra_s_str_qr_idk = '';
        $ks_str_qr_idk = '';

        if(!empty($tmp_data))
        {
          foreach ($tmp_data as $rc_typ) {         
            $str_qr_idk.= (!empty($str_qr_idk) ? ',' : '')."SUM(Kd_contyp=$rc_typ[Kd_contyp]) AS j_typ_$rc_typ[Kd_contyp]";            
          } 
        }

    $tb = new tb_gen('dbo_family');
    //$tb->sql_from="vw_fam_indv";
    $tb->sql_select = "COUNT(*) AS jd,
                       $str_qr_idk";

    $dt_tb=array();
    $arrjml = array();
    $i=1;
    foreach($data as $row)
    {
      $tmp_dt_tb=array();
      $tmp_dt_tb[]=$i;
      $tmp_dt_tb[]=$row['no_unit_detail'];
      $tmp_dt_tb[]='PRA SEJAHTERA';
      
      $kd_wlq=$this->getkdwl(($idkec==0 ? $row['id_unit_detail'] : $idkec ),
      ((($idkec!=0) and ($iddesa == 0)) ? $row['id_unit_detail'] : $iddesa),
      ((($idkec!=0) and ($iddesa != 0) and ($iddusun==0)) ? $row['id_unit_detail']  : $iddusun),
      ((($idkec!=0) and ($iddesa != 0) and ($iddusun!=0) and ($idrt==0)) ? $row['id_unit_detail']  : $idrt));  

      $data1 = $tb->getData("$kd_wlq pus='1' and (".$this->arr_ks['pra_s'].")");
      $rc = $this->build_rc($data1);      
     
      $jml=0;
      $j=1;
      if(!empty($rc)){  
        foreach ($rc as $key => $value) {
          
            $tmp_dt_tb[]=number_format($value,0,',','.'); 
            if($j>1){ 
              $jml=$jml+$value;
            }

            $arrjml[$key] = $this->fjml_ttl($arrjml,$key,$value,'');
         $j++;
        }

        $tmp_dt_tb[]=number_format($jml,0,',','.');
        $tmp_dt_tb[]=number_format($this->fprosen($jml,'',$rc,'jd'),2,',','.').'%';
        $arrjml['jml'] = $this->fjml_ttl($arrjml,'jml',$jml,''); 
        $arrjml['prosen'] =  $this->fprosen($arrjml,'jml',$arrjml,'jd') ;
        
      }else{
          for($j=1;$j<11;$j++)
          {
            $tmp_dt_tb[]=0;
          }
          $tmp_dt_tb[]='0%';
        }     


      $dt_tb[] = $tmp_dt_tb;
      $i++;
    } 

       
    $footer_tb=array();
        $tmp_footer=array();
        $tmp_footer[]='PRA SEJAHTERA';
        foreach ($arrjml as $key=>$value) {
          
            if($key!='prosen'){ 
             $tmp_footer[$key]= number_format($value,0,',','.');
            }else{
             $tmp_footer[$key]= number_format($value,2,',','.').'%';
            } 
         
        } 

        $footer_tb = $tmp_footer;
    return array('isi_tb'=>$dt_tb,'footer_tb'=>$footer_tb);

  }

  function getdtmenu03_tab5($idkec,$iddesa,$iddusun,$idrt){

    
    $kd_wl=$this->getkdwl($idkec,$iddesa,$iddusun,$idrt,'','','id_unit_detail_idk');    
    
    $dt = new dt_unit_detail;              
    $data = $dt->getdata("$kd_wl");

    $this->arrayks();
                
        $tmp_dt = new dt_contr_typ;
        $tmp_data = $tmp_dt->getdata('');

        $str_qr_idk = '';
        $pra_s_str_qr_idk = '';
        $ks_str_qr_idk = '';

        if(!empty($tmp_data))
        {
          foreach ($tmp_data as $rc_typ) {         
            $str_qr_idk.= (!empty($str_qr_idk) ? ',' : '')."SUM(Kd_contyp=$rc_typ[Kd_contyp]) AS j_typ_$rc_typ[Kd_contyp]";            
          } 
        }

    $tb = new tb_gen('dbo_family');
    //$tb->sql_from="vw_fam_indv";
    $tb->sql_select = "COUNT(*) AS jd,
                       $str_qr_idk";

    $dt_tb=array();
    $arrjml = array();
    $i=1;
    foreach($data as $row)
    {
      $tmp_dt_tb=array();
      $tmp_dt_tb[]=$i;
      $tmp_dt_tb[]=$row['no_unit_detail'];
      $tmp_dt_tb[]='KS I';
      
      $kd_wlq=$this->getkdwl(($idkec==0 ? $row['id_unit_detail'] : $idkec ),
      ((($idkec!=0) and ($iddesa == 0)) ? $row['id_unit_detail'] : $iddesa),
      ((($idkec!=0) and ($iddesa != 0) and ($iddusun==0)) ? $row['id_unit_detail']  : $iddusun),
      ((($idkec!=0) and ($iddesa != 0) and ($iddusun!=0) and ($idrt==0)) ? $row['id_unit_detail']  : $idrt));  

      $data1 = $tb->getData("$kd_wlq pus='1' and (".$this->arr_ks['ks_1'].")");
      $rc = $this->build_rc($data1);      
     
      $jml=0;
      $j=1;
      if(!empty($rc)){  
        foreach ($rc as $key => $value) {
          
            $tmp_dt_tb[]=number_format($value,0,',','.'); 
            if($j>1){ 
              $jml=$jml+$value;
            }

            $arrjml[$key] = $this->fjml_ttl($arrjml,$key,$value,'');
         $j++;
        }

        $tmp_dt_tb[]=number_format($jml,0,',','.');
        $tmp_dt_tb[]=number_format($this->fprosen($jml,'',$rc,'jd'),2,',','.').'%';
        $arrjml['jml'] = $this->fjml_ttl($arrjml,'jml',$jml,''); 
        $arrjml['prosen'] =  $this->fprosen($arrjml,'jml',$arrjml,'jd') ;
        
      }else{
          for($j=1;$j<11;$j++)
          {
            $tmp_dt_tb[]=0;
          }
          $tmp_dt_tb[]='0%';
        }     


      $dt_tb[] = $tmp_dt_tb;
      $i++;
    } 

       
    $footer_tb=array();
        $tmp_footer=array();
        $tmp_footer[]='KS I';
        foreach ($arrjml as $key=>$value) {
          
            if($key!='prosen'){ 
             $tmp_footer[$key]= number_format($value,0,',','.');
            }else{
             $tmp_footer[$key]= number_format($value,2,',','.').'%';
            } 
         
        } 

        $footer_tb = $tmp_footer;
    return array('isi_tb'=>$dt_tb,'footer_tb'=>$footer_tb);

  }

  function getdtmenu03_tab6($idkec,$iddesa,$iddusun,$idrt){

    $kd_wl=$this->getkdwl($idkec,$iddesa,$iddusun,$idrt,'','','id_unit_detail_idk');

    $u1549 = $this->getrentang(15,49);
    
    $dt = new dt_unit_detail;              
    $data = $dt->getdata("$kd_wl");

    $this->arrayks();

    $tb = new tb_gen('tbgen');
    $tb->sql_from="vw_fam_indv";
    $tb->sql_select = "SUM( Kd_fammbrtyp=1) AS j_rt,".
                      "SUM( Kd_fammbrtyp=1 AND  Kd_gen=1) AS j_lk_kk,".
                      "SUM( Kd_fammbrtyp=1 AND  Kd_gen=2) AS j_pr_kk,".
                      "SUM( Kd_fammbrtyp=1 AND  Kd_emp!=6) AS j_krj_kk,".
                      "SUM( Kd_fammbrtyp=1 AND  Kd_emp=6) AS j_tkrj_kk,".
                      "SUM( Kd_fammbrtyp=1 AND  Kd_martl=2) AS j_kwn_kk,".
                      "SUM( Kd_fammbrtyp=1 AND  Kd_martl!=2) AS j_tkwn_kk,".
                      "SUM( Kd_fammbrtyp=1 AND  Kd_edu=2) AS j_ttmt_sd_kk,".
                      "SUM( Kd_fammbrtyp=1 AND  (Kd_edu=3 OR  Kd_edu=5)) AS j_tmt_sd_sltp_kk,".
                      "SUM( Kd_fammbrtyp=1 AND  Kd_edu=7) AS j_tmt_slta_kk,".
                      "SUM( Kd_fammbrtyp=1 AND  Kd_edu=9) AS j_tmt_ak_pt_kk,".
                      "SUM( Bantuan_modal='1' AND  Kd_fammbrtyp=1) AS j_btm_kk,".
                      "SUM( Bantuan_modal='0' AND  Kd_fammbrtyp=1) AS j_tbtm_kk,".
                      "SUM( Kd_gen=1) AS j_lk_jiwa,".
                      "SUM( Kd_gen=2) AS j_pr_jiwa,".
                      "SUM( Kd_gen=2 AND ($u1549)) AS j_wus";

    $dt_tb=array();
    $arrjml = array();
    $i=1;
    foreach($data as $row)
    {
      $tmp_dt_tb=array();
      $tmp_dt_tb[]=$i;
      $tmp_dt_tb[]=$row['no_unit_detail'];
      $tmp_dt_tb[]='PRA SEJAHTERA';
      
      $kd_wlq=$this->getkdwl(($idkec==0 ? $row['id_unit_detail'] : $idkec ),
      ((($idkec!=0) and ($iddesa == 0)) ? $row['id_unit_detail'] : $iddesa),
      ((($idkec!=0) and ($iddesa != 0) and ($iddusun==0)) ? $row['id_unit_detail']  : $iddusun),
      ((($idkec!=0) and ($iddesa != 0) and ($iddusun!=0) and ($idrt==0)) ? $row['id_unit_detail']  : $idrt));  

      $data1 = $tb->getData("$kd_wlq Kd_mutasi IS NULL and (".$this->arr_ks['pra_s'].")");
      $rc = $this->build_rc($data1);
      
      $tmp_dt_tb[]=$this->frupiah($rc,'j_rt');
      $arrjml['jml10'] = $this->fjml_ttl($arrjml,'jml10',$rc,'j_rt');
      

      $j=1;
      if(!empty($rc)){  
        foreach ($rc as $key => $value) {
          if($j>1 and $j<=15){
            $tmp_dt_tb[]=number_format($value,0,',','.'); 
            $arrjml[$key] = $this->fjml_ttl($arrjml,$key,$value,'');
          }      

          $j++;
        }
        $tmp_dt_tb[]=$this->frupiah($rc['j_lk_jiwa']+$rc['j_pr_jiwa'],'');
        $arrjml['jml11'] = $this->fjml_ttl($arrjml,'jml11',$rc['j_lk_jiwa']+$rc['j_pr_jiwa'],'');
        $tmp_dt_tb[]=$this->frupiah($rc,'j_wus');
        $arrjml['jml12'] = $this->fjml_ttl($arrjml,'jml12',$rc,'j_wus');
      }else{
          for($j=1;$j<17;$j++)
          {
            $tmp_dt_tb[]=0;
          }
          
        } 
      $dt_tb[] = $tmp_dt_tb;
      $i++;
    } 

       
    $footer_tb=array();
        $tmp_footer=array();
        $tmp_footer[]='PRA SEJAHTERA';
        foreach ($arrjml as $key=>$value) {          
            $tmp_footer[$key]= number_format($value,0,',','.');          
        } 

        $footer_tb = $tmp_footer;
    return array('isi_tb'=>$dt_tb,'footer_tb'=>$footer_tb);

  }

  function getdtmenu03_tab7($idkec,$iddesa,$iddusun,$idrt){

    $kd_wl=$this->getkdwl($idkec,$iddesa,$iddusun,$idrt,'','','id_unit_detail_idk');    
    
    $dt = new dt_unit_detail;              
    $data = $dt->getdata("$kd_wl");

    $this->arrayks();
        
        $u01 = $this->getrentang(0,1);
        $u15 = $this->getrentang(1,4);
        $u56 = $this->getrentang(5,6);
        $u715 = $this->getrentang(7,15);
        
        $u1621 = $this->getrentang(16,21);
        $u2259 = $this->getrentang(22,59);
        $u60 = $this->getrentang(60);

        $u020 = $this->getrentang(0,19);
        $u2029 = $this->getrentang(20,29);
        $u3049 = $this->getrentang(30,49);

        $tmp_dt = new dt_non_acptr_reas;
        $tmp_data = $tmp_dt->getdata('');
        
        $str_reas = '';
        $str_reas_pra_s = '';
        $str_reas_ks = '';

        if(!empty($tmp_data))
        {
          foreach ($tmp_data as $rc_reas) {         
            $str_reas.= (!empty($str_reas) ? ',' : '')."SUM(Kd_nonacptr=".$rc_reas['Kd_nonacptr']." AND Kd_fammbrtyp=1) AS j_reas_".$rc_reas['Kd_nonacptr'];
          } 
        }

    $tb = new tb_gen('tbgen');
    $tb->sql_from="vw_fam_indv";
    $tb->sql_select = "SUM(($u01) AND  Posyandu='1') AS j_blt_0_1_pos,".
                      "SUM(($u01) AND  Posyandu='0') AS j_blt_0_1_tpos,".
                      "SUM(($u15) AND  Posyandu='1') AS j_blt_1_5_pos,".
                      "SUM(($u15) AND  Posyandu='0') AS j_blt_1_5_tpos,".
                      "SUM($u56) AS j_5_6_th,".                                   
                      "SUM(($u715) AND  Kd_edu!=0 AND  Kd_gen=1) AS j_lk_sklh_7_15,".
                      "SUM(($u715) AND  Kd_edu!=0 AND  Kd_gen=2) AS j_pr_sklh_7_15,".
                      "SUM(($u715) AND  Kd_edu=0 AND  Kd_gen=1) AS j_lk_tsklh_7_15,".
                      "SUM(($u715) AND  Kd_edu=0 AND  Kd_gen=2) AS j_pr_tsklh_7_15,".
                      "SUM($u1621) AS j_16_21_th,".
                      "SUM($u2259) AS j_22_59_th,".
                      "SUM($u60) AS j_60_th,".
                      "SUM( pus='1' AND  Kd_fammbrtyp=1) AS j_pus,".
                      "SUM( pus='1' AND  Kd_fammbrtyp=2 AND ($u020)) AS j_20_th_pus,".
                      "SUM( pus='1' AND  Kd_fammbrtyp=2 AND ($u2029)) AS j_20_29_th_pus,".
                      "SUM( pus='1' AND  Kd_fammbrtyp=2 AND ($u3049)) AS j_30_49_th_pus,".
                      "SUM( Kd_consrc=1 AND  Kd_fammbrtyp=1) AS j_pmt_kb,".
                      "SUM( Kd_consrc=2 AND  Kd_fammbrtyp=1) AS j_swst_kb,".
                      "SUM(( Kd_implan=0 AND  Kd_implan IS NOT NULL AND  Kd_contyp=4 AND  Kd_consrc IS NOT NULL AND  Kd_consrc!=0) AND  Kd_fammbrtyp=1) AS j_impl,".
                      $str_reas;

    $dt_tb=array();
    $arrjml = array();
    $i=1;
    foreach($data as $row)
    {
      $tmp_dt_tb=array();
      $tmp_dt_tb[]=$i;
      $tmp_dt_tb[]=$row['no_unit_detail'];
      $tmp_dt_tb[]='PRA SEJAHTERA';
      
      $kd_wlq=$this->getkdwl(($idkec==0 ? $row['id_unit_detail'] : $idkec ),
      ((($idkec!=0) and ($iddesa == 0)) ? $row['id_unit_detail'] : $iddesa),
      ((($idkec!=0) and ($iddesa != 0) and ($iddusun==0)) ? $row['id_unit_detail']  : $iddusun),
      ((($idkec!=0) and ($iddesa != 0) and ($iddusun!=0) and ($idrt==0)) ? $row['id_unit_detail']  : $idrt));  

      $data1 = $tb->getData("$kd_wlq Kd_mutasi IS NULL and (".$this->arr_ks['pra_s'].")");
      $rc = $this->build_rc($data1);

      
     
      if(!empty($rc)){  
        foreach ($rc as $key => $value) {          
            $tmp_dt_tb[]=number_format($value,0,',','.'); 
            $arrjml[$key] = $this->fjml_ttl($arrjml,$key,$value,'');            
        }       
      }else{
          for($j=1;$j<30;$j++)
          {
            $tmp_dt_tb[]=0;
          }          
        }      


      $dt_tb[] = $tmp_dt_tb;
      $i++;
    } 

       
    $footer_tb=array();
        $tmp_footer=array();
        $tmp_footer[]='PRA SEJAHTERA';
        foreach ($arrjml as $key=>$value) {          
            $tmp_footer[$key]= number_format($value,0,',','.');          
        } 
        $footer_tb = $tmp_footer;
    return array('isi_tb'=>$dt_tb,'footer_tb'=>$footer_tb);

  }

  function getdtmenu03_tab8($idkec,$iddesa,$iddusun,$idrt){

    $dt_tb=array();
    $footer_tb=array();
    return array('isi_tb'=>$dt_tb,'footer_tb'=>$footer_tb);

  }

  function getdtmenu03_tab9($idkec,$iddesa,$iddusun,$idrt){

    $kd_wl=$this->getkdwl($idkec,$iddesa,$iddusun,$idrt,'','','id_unit_detail_idk');

    $u1549 = $this->getrentang(15,49);
    
    $dt = new dt_unit_detail;              
    $data = $dt->getdata("$kd_wl");

    $this->arrayks();

    $tb = new tb_gen('tbgen');
    $tb->sql_from="vw_fam_indv";
    $tb->sql_select = "SUM( Kd_fammbrtyp=1) AS j_rt,".
                      "SUM( Kd_fammbrtyp=1 AND  Kd_gen=1) AS j_lk_kk,".
                      "SUM( Kd_fammbrtyp=1 AND  Kd_gen=2) AS j_pr_kk,".
                      "SUM( Kd_fammbrtyp=1 AND  Kd_emp!=6) AS j_krj_kk,".
                      "SUM( Kd_fammbrtyp=1 AND  Kd_emp=6) AS j_tkrj_kk,".
                      "SUM( Kd_fammbrtyp=1 AND  Kd_martl=2) AS j_kwn_kk,".
                      "SUM( Kd_fammbrtyp=1 AND  Kd_martl!=2) AS j_tkwn_kk,".
                      "SUM( Kd_fammbrtyp=1 AND  Kd_edu=2) AS j_ttmt_sd_kk,".
                      "SUM( Kd_fammbrtyp=1 AND  (Kd_edu=3 OR  Kd_edu=5)) AS j_tmt_sd_sltp_kk,".
                      "SUM( Kd_fammbrtyp=1 AND  Kd_edu=7) AS j_tmt_slta_kk,".
                      "SUM( Kd_fammbrtyp=1 AND  Kd_edu=9) AS j_tmt_ak_pt_kk,".
                      "SUM( Bantuan_modal='1' AND  Kd_fammbrtyp=1) AS j_btm_kk,".
                      "SUM( Bantuan_modal='0' AND  Kd_fammbrtyp=1) AS j_tbtm_kk,".
                      "SUM( Kd_gen=1) AS j_lk_jiwa,".
                      "SUM( Kd_gen=2) AS j_pr_jiwa,".
                      "SUM( Kd_gen=2 AND ($u1549)) AS j_wus";

    $dt_tb=array();
    $arrjml = array();
    $i=1;
    foreach($data as $row)
    {
      $tmp_dt_tb=array();
      $tmp_dt_tb[]=$i;
      $tmp_dt_tb[]=$row['no_unit_detail'];
      $tmp_dt_tb[]='KS I';
      
      $kd_wlq=$this->getkdwl(($idkec==0 ? $row['id_unit_detail'] : $idkec ),
      ((($idkec!=0) and ($iddesa == 0)) ? $row['id_unit_detail'] : $iddesa),
      ((($idkec!=0) and ($iddesa != 0) and ($iddusun==0)) ? $row['id_unit_detail']  : $iddusun),
      ((($idkec!=0) and ($iddesa != 0) and ($iddusun!=0) and ($idrt==0)) ? $row['id_unit_detail']  : $idrt));  

      $data1 = $tb->getData("$kd_wlq Kd_mutasi IS NULL and (".$this->arr_ks['ks_1'].")");
      $rc = $this->build_rc($data1);
      
      $tmp_dt_tb[]=$this->frupiah($rc,'j_rt');
      $arrjml['jml10'] = $this->fjml_ttl($arrjml,'jml10',$rc,'j_rt');
      

      $j=1;
      if(!empty($rc)){  
        foreach ($rc as $key => $value) {
          if($j>1 and $j<=15){
            $tmp_dt_tb[]=number_format($value,0,',','.'); 
            $arrjml[$key] = $this->fjml_ttl($arrjml,$key,$value,'');
          }      

          $j++;
        }
        $tmp_dt_tb[]=$this->frupiah($rc['j_lk_jiwa']+$rc['j_pr_jiwa'],'');
        $arrjml['jml11'] = $this->fjml_ttl($arrjml,'jml11',$rc['j_lk_jiwa']+$rc['j_pr_jiwa'],'');
        $tmp_dt_tb[]=$this->frupiah($rc,'j_wus');
        $arrjml['jml12'] = $this->fjml_ttl($arrjml,'jml12',$rc,'j_wus');
      }else{
          for($j=1;$j<17;$j++)
          {
            $tmp_dt_tb[]=0;
          }
          
        } 
      $dt_tb[] = $tmp_dt_tb;
      $i++;
    } 

       
    $footer_tb=array();
        $tmp_footer=array();
        $tmp_footer[]='KS I';
        foreach ($arrjml as $key=>$value) {          
            $tmp_footer[$key]= number_format($value,0,',','.');          
        } 

        $footer_tb = $tmp_footer;
    return array('isi_tb'=>$dt_tb,'footer_tb'=>$footer_tb);

  }

  function getdtmenu03_tab10($idkec,$iddesa,$iddusun,$idrt){

    $kd_wl=$this->getkdwl($idkec,$iddesa,$iddusun,$idrt,'','','id_unit_detail_idk');    
    
    $dt = new dt_unit_detail;              
    $data = $dt->getdata("$kd_wl");

    $this->arrayks();
        
        $u01 = $this->getrentang(0,1);
        $u15 = $this->getrentang(1,4);
        $u56 = $this->getrentang(5,6);
        $u715 = $this->getrentang(7,15);
        
        $u1621 = $this->getrentang(16,21);
        $u2259 = $this->getrentang(22,59);
        $u60 = $this->getrentang(60);

        $u020 = $this->getrentang(0,19);
        $u2029 = $this->getrentang(20,29);
        $u3049 = $this->getrentang(30,49);

        $tmp_dt = new dt_non_acptr_reas;
        $tmp_data = $tmp_dt->getdata('');
        
        $str_reas = '';
        $str_reas_pra_s = '';
        $str_reas_ks = '';

        if(!empty($tmp_data))
        {
          foreach ($tmp_data as $rc_reas) {         
            $str_reas.= (!empty($str_reas) ? ',' : '')."SUM(Kd_nonacptr=".$rc_reas['Kd_nonacptr']." AND Kd_fammbrtyp=1) AS j_reas_".$rc_reas['Kd_nonacptr'];
          } 
        }

    $tb = new tb_gen('tbgen');
    $tb->sql_from="vw_fam_indv";
    $tb->sql_select = "SUM(($u01) AND  Posyandu='1') AS j_blt_0_1_pos,".
                      "SUM(($u01) AND  Posyandu='0') AS j_blt_0_1_tpos,".
                      "SUM(($u15) AND  Posyandu='1') AS j_blt_1_5_pos,".
                      "SUM(($u15) AND  Posyandu='0') AS j_blt_1_5_tpos,".
                      "SUM($u56) AS j_5_6_th,".                                   
                      "SUM(($u715) AND  Kd_edu!=0 AND  Kd_gen=1) AS j_lk_sklh_7_15,".
                      "SUM(($u715) AND  Kd_edu!=0 AND  Kd_gen=2) AS j_pr_sklh_7_15,".
                      "SUM(($u715) AND  Kd_edu=0 AND  Kd_gen=1) AS j_lk_tsklh_7_15,".
                      "SUM(($u715) AND  Kd_edu=0 AND  Kd_gen=2) AS j_pr_tsklh_7_15,".
                      "SUM($u1621) AS j_16_21_th,".
                      "SUM($u2259) AS j_22_59_th,".
                      "SUM($u60) AS j_60_th,".
                      "SUM( pus='1' AND  Kd_fammbrtyp=1) AS j_pus,".
                      "SUM( pus='1' AND  Kd_fammbrtyp=2 AND ($u020)) AS j_20_th_pus,".
                      "SUM( pus='1' AND  Kd_fammbrtyp=2 AND ($u2029)) AS j_20_29_th_pus,".
                      "SUM( pus='1' AND  Kd_fammbrtyp=2 AND ($u3049)) AS j_30_49_th_pus,".
                      "SUM( Kd_consrc=1 AND  Kd_fammbrtyp=1) AS j_pmt_kb,".
                      "SUM( Kd_consrc=2 AND  Kd_fammbrtyp=1) AS j_swst_kb,".
                      "SUM(( Kd_implan=0 AND  Kd_implan IS NOT NULL AND  Kd_contyp=4 AND  Kd_consrc IS NOT NULL AND  Kd_consrc!=0) AND  Kd_fammbrtyp=1) AS j_impl,".
                      $str_reas;

    $dt_tb=array();
    $arrjml = array();
    $i=1;
    foreach($data as $row)
    {
      $tmp_dt_tb=array();
      $tmp_dt_tb[]=$i;
      $tmp_dt_tb[]=$row['no_unit_detail'];
      $tmp_dt_tb[]='KS I';
      
      $kd_wlq=$this->getkdwl(($idkec==0 ? $row['id_unit_detail'] : $idkec ),
      ((($idkec!=0) and ($iddesa == 0)) ? $row['id_unit_detail'] : $iddesa),
      ((($idkec!=0) and ($iddesa != 0) and ($iddusun==0)) ? $row['id_unit_detail']  : $iddusun),
      ((($idkec!=0) and ($iddesa != 0) and ($iddusun!=0) and ($idrt==0)) ? $row['id_unit_detail']  : $idrt));  

      $data1 = $tb->getData("$kd_wlq Kd_mutasi IS NULL and (".$this->arr_ks['ks_1'].")");
      $rc = $this->build_rc($data1);

      
     
      if(!empty($rc)){  
        foreach ($rc as $key => $value) {          
            $tmp_dt_tb[]=number_format($value,0,',','.'); 
            $arrjml[$key] = $this->fjml_ttl($arrjml,$key,$value,'');            
        }       
      }else{
          for($j=1;$j<30;$j++)
          {
            $tmp_dt_tb[]=0;
          }          
        }      


      $dt_tb[] = $tmp_dt_tb;
      $i++;
    } 

       
    $footer_tb=array();
        $tmp_footer=array();
        $tmp_footer[]='KS I';
        foreach ($arrjml as $key=>$value) {          
            $tmp_footer[$key]= number_format($value,0,',','.');          
        } 
        $footer_tb = $tmp_footer;
    return array('isi_tb'=>$dt_tb,'footer_tb'=>$footer_tb);

  }

  function getdtmenu03_tab11($idkec,$iddesa,$iddusun,$idrt){

    $dt_tb=array();
    $footer_tb=array();
    return array('isi_tb'=>$dt_tb,'footer_tb'=>$footer_tb);

  }

}   