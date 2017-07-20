<?php require_once('shared.php');

class dt_rekapitulasi
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
		return $tmp_prosen;
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

	function getdtmenu401($idkec,$iddesa,$iddusun,$idrt){ 
		
        if(empty($idrt)){
		 $kd_wl=$this->getkdwl($idkec,$iddesa,$iddusun,$idrt,'','','id_unit_detail_idk');
        }else{
         $kd_wl=$this->getkdwl($idkec,$iddesa,$iddusun,$idrt); 	
        }
		
		$this->arrayks();

		$arrjml = array();
        if(empty($idrt)){
		  $dt = new dt_unit_detail;              
		  $data = $dt->getdata("$kd_wl");  

	 	  $tb = new tb_gen('tbgen');
		  $tb->sql_from="vw_fam_indv";		
		  $tb->sql_select = "SUM(Kd_fammbrtyp=1) AS j_kk,
		                   COUNT(*) AS j_jiwa,
		                   SUM(Kd_fammbrtyp=1 AND (".$this->arr_ks['pra_s'].")) AS j_pra_s,
		                   SUM(Kd_fammbrtyp=1 AND (".$this->arr_ks['ks_1'].")) AS j_ks";                           
		}else{
          $tb = new tb_gen('tbgen');
		  $tb->sql_from="vw_fam_indv";		
		  $tb->sql_select = "kd_fam,COUNT(*) AS jml_jiwa,Kd_prosplvl"; 
		  $tb->sql_groupby = 'Kd_fam';
		  $tb->sql_orderby = 'Kd_fam';              
		  $data = $tb->getData("$kd_wl (".$this->arr_ks['pra_s']." OR ".$this->arr_ks['ks_1'].") and (Kd_mutasi IS NULL)");

		  $tb_indv = new tb_gen('dbo_individu');  
		  $tb_indv->sql_select = "Nama";
		  $arrjml['jml_jiwa']=0;
		  $arrjml['pra']=0;
		  $arrjml['ks']=0;
		}

		$dt_tb=array();
		$i=1;
		
		$jml_pra=1;
		$jml_ks=1;

        if(!empty($data)){
			foreach($data as $row)
			{
				$tmp_dt_tb=array();			

				if(empty($idrt))
				{
				  $tmp_dt_tb[]=$i;
				  $tmp_dt_tb[]=$row['no_unit_detail'];    
				

				  $kd_wlq=$this->getkdwl(($idkec==0 ? $row['id_unit_detail'] : $idkec ),
				  ( (($idkec!=0) and ($iddesa == 0)) ? $row['id_unit_detail'] : $iddesa),
				  ( (($idkec!=0) and ($iddesa != 0) and ($iddusun==0)) ? $row['id_unit_detail']  : $iddusun),
				  ((($idkec!=0) and ($iddesa != 0) and ($iddusun!=0) and ($idrt==0)) ? $row['id_unit_detail']  : $idrt));          
				
				  $data1 = $tb->getData("$kd_wlq (".$this->arr_ks['pra_s']." OR ".$this->arr_ks['ks_1'].") AND Kd_mutasi IS NULL");			
				  $rc = $this->build_rc($data1);
	            
	              $tmp_dt_tb[]=number_format($rc['j_kk'],0,',','.');
	              $arrjml['j_kk']=$this->fjml_ttl($arrjml,'j_kk',$rc,'j_kk');

	              $tmp_dt_tb[]=number_format($rc['j_jiwa'],0,',','.');
	              $arrjml['j_jiwa']=$this->fjml_ttl($arrjml,'j_jiwa',$rc,'j_jiwa');
	            
	              $tmp_dt_tb[]=number_format($rc['j_pra_s'],0,',','.');
	              $arrjml['j_pra_s']=$this->fjml_ttl($arrjml,'j_pra_s',$rc,'j_pra_s');            
	            
	              $tmp_dt_tb[]=number_format($rc['j_ks'],0,',','.');
	              $arrjml['j_ks']=$this->fjml_ttl($arrjml,'j_ks',$rc,'j_ks'); 
	            } else{
	            	$tmp_dt_tb[]=$row['Kd_fam'];
	               
	                $data1 = $tb_indv->getData("Kd_fam='$row[Kd_fam]' and Kd_fammbrtyp=1");			
				    $rc = $this->build_rc($data1);     

				    $tmp_dt_tb[]=$rc['Nama'];
				    $tmp_dt_tb[]=$row['jml_jiwa'];
				    $arrjml['jml_jiwa']=$this->fjml_ttl($arrjml,'jml_jiwa',$row,'jml_jiwa');
				    
				    if(($row['Kd_prosplvl']==1) or ($row['Kd_prosplvl']==6)){
				      $tmp_dt_tb[]='V';
				      $arrjml['pra'] = $this->fjml_ttl($arrjml,'pra',$jml_pra,'');
				    }else{
				      $tmp_dt_tb[]=' ';
				    }

				    if(($row['Kd_prosplvl']==2) or ($row['Kd_prosplvl']==7)){
				      $tmp_dt_tb[]='V';
				      $arrjml['ks'] = $this->fjml_ttl($arrjml,'ks',$jml_ks,'');
				    }else{
				      $tmp_dt_tb[]=' ';
				    } 
	            }           

				$dt_tb[] = $tmp_dt_tb;
				$i++;
			}	
		}
		
		$footer_tb=array();
		$tmp_footer=array();       

		foreach ($arrjml as $key=>$value) {
			$tmp_footer[]= number_format($value,0,',','.');     
		}           

		$footer_tb[] = $tmp_footer;          
		
		return array('isi_tb'=>$dt_tb,'footer_tb'=>$footer_tb); 
	}  

	function getdtmenu402($idkec,$iddesa,$iddusun,$idrt){ 
		
        if(empty($idrt)){
		 $kd_wl=$this->getkdwl($idkec,$iddesa,$iddusun,$idrt,'','','id_unit_detail_idk');
        }else{
         $kd_wl=$this->getkdwl($idkec,$iddesa,$iddusun,$idrt); 	
        }
		
		$this->arrayks();

		$arrjml = array();
        if(empty($idrt)){
		  $dt = new dt_unit_detail;              
		  $data = $dt->getdata("$kd_wl");  

	 	  $tb = new tb_gen('tbgen');
		  $tb->sql_from="vw_fam_indv";		
		  $tb->sql_select = "SUM(Kd_fammbrtyp=1) AS j_kk,
		                     COUNT(*) AS j_jiwa,
		                     SUM(Kd_fammbrtyp=1 AND Kd_prosplvl=6) AS j_pra_s_alek,
		                     SUM(Kd_fammbrtyp=1 AND Kd_prosplvl=1) AS j_pra_s_non_alek,
		                     SUM(Kd_fammbrtyp=1 AND Kd_prosplvl=7) AS j_ks_alek,
		                     SUM(Kd_fammbrtyp=1 AND Kd_prosplvl=2) AS j_ks_non_alek ";                           
		}else{
          $tb = new tb_gen('tbgen');
		  $tb->sql_from="vw_fam_indv";		
		  $tb->sql_select = "kd_fam,COUNT(*) AS jml_jiwa,Kd_prosplvl"; 
		  $tb->sql_groupby = 'Kd_fam';
		  $tb->sql_orderby = 'Kd_fam';              
		  $data = $tb->getData("$kd_wl (".$this->arr_ks['pra_s']." OR ".$this->arr_ks['ks_1'].") and (Kd_mutasi IS NULL)");

		  $tb_indv = new tb_gen('dbo_individu');  
		  $tb_indv->sql_select = "Nama";
		  $arrjml['jml_jiwa']=0;
		  $arrjml['pra_alek']=0;
		  $arrjml['pra_non_alek']=0;
		  $arrjml['ks_alek']=0;
		  $arrjml['ks_non_alek']=0;
		}

		$dt_tb=array();
		$i=1;
		
		$jml_pra_alek=1;
		$jml_pra_non_alek=1;
		$jml_ks_alek=1;
		$jml_ks_non_alek=1;

        if(!empty($data)){
			foreach($data as $row)
			{
				$tmp_dt_tb=array();			

				if(empty($idrt))
				{
				  $tmp_dt_tb[]=$i;
				  $tmp_dt_tb[]=$row['no_unit_detail'];    
				

				  $kd_wlq=$this->getkdwl(($idkec==0 ? $row['id_unit_detail'] : $idkec ),
				  ( (($idkec!=0) and ($iddesa == 0)) ? $row['id_unit_detail'] : $iddesa),
				  ( (($idkec!=0) and ($iddesa != 0) and ($iddusun==0)) ? $row['id_unit_detail']  : $iddusun),
				  ((($idkec!=0) and ($iddesa != 0) and ($iddusun!=0) and ($idrt==0)) ? $row['id_unit_detail']  : $idrt));          
				
				  $data1 = $tb->getData("$kd_wlq (".$this->arr_ks['pra_s']." OR ".$this->arr_ks['ks_1'].") AND Kd_mutasi IS NULL");			
				  $rc = $this->build_rc($data1);
	            
	              $tmp_dt_tb[]=$this->frupiah($rc,'j_kk');
	              $arrjml['j_kk']=$this->fjml_ttl($arrjml,'j_kk',$rc,'j_kk');

	              $tmp_dt_tb[]=$this->frupiah($rc,'j_jiwa');
	              $arrjml['j_jiwa']=$this->fjml_ttl($arrjml,'j_jiwa',$rc,'j_jiwa');
	            
	              $tmp_dt_tb[]=$this->frupiah($rc,'j_pra_s_alek');
	              $arrjml['j_pra_s_alek']=$this->fjml_ttl($arrjml,'j_pra_s_alek',$rc,'j_pra_s_alek'); 

	              $tmp_dt_tb[]=$this->frupiah($rc,'j_pra_s_non_alek');
	              $arrjml['j_pra_s_non_alek']=$this->fjml_ttl($arrjml,'j_pra_s_non_alek',$rc,'j_pra_s_non_alek');            
	            
	              $tmp_dt_tb[]=$this->frupiah($rc,'j_ks_alek');
	              $arrjml['j_ks_alek']=$this->fjml_ttl($arrjml,'j_ks_alek',$rc,'j_ks_alek');

	              $tmp_dt_tb[]=$this->frupiah($rc,'j_ks_non_alek');
	              $arrjml['j_ks_non_alek']=$this->fjml_ttl($arrjml,'j_ks_non_alek',$rc,'j_ks_non_alek');

	            } else{
	            	$tmp_dt_tb[]=$row['Kd_fam'];
	               
	                $data1 = $tb_indv->getData("Kd_fam='$row[Kd_fam]' and Kd_fammbrtyp=1");			
				    $rc = $this->build_rc($data1);     

				    $tmp_dt_tb[]=$rc['Nama'];
				    $tmp_dt_tb[]=$row['jml_jiwa'];
				    $arrjml['jml_jiwa']=$this->fjml_ttl($arrjml,'jml_jiwa',$row,'jml_jiwa');
				    
				    if(($row['Kd_prosplvl']==6)){
				      $tmp_dt_tb[]='V';
				      $arrjml['pra_alek'] = $this->fjml_ttl($arrjml,'pra_alek',$jml_pra_alek,'');
				    }else{
				      $tmp_dt_tb[]=' ';
				    }

				    if(($row['Kd_prosplvl']==1)){
				      $tmp_dt_tb[]='V';
				      $arrjml['pra_non_alek'] = $this->fjml_ttl($arrjml,'pra_non_alek',$jml_pra_non_alek,'');
				    }else{
				      $tmp_dt_tb[]=' ';
				    }


				    if(($row['Kd_prosplvl']==7)){
				      $tmp_dt_tb[]='V';
				      $arrjml['ks_alek'] = $this->fjml_ttl($arrjml,'ks_alek',$jml_ks_alek,'');
				    }else{
				      $tmp_dt_tb[]=' ';
				    } 

				    if(($row['Kd_prosplvl']==2)){
				      $tmp_dt_tb[]='V';
				      $arrjml['ks_non_alek'] = $this->fjml_ttl($arrjml,'ks_non_alek',$jml_ks_non_alek,'');
				    }else{
				      $tmp_dt_tb[]=' ';
				    } 



	            }           

				$dt_tb[] = $tmp_dt_tb;
				$i++;
			}	
		}
		
		$footer_tb=array();
		$tmp_footer=array();       

		foreach ($arrjml as $key=>$value) {
			$tmp_footer[]= number_format($value,0,',','.');     
		}           

		$footer_tb[] = $tmp_footer;          
		
		return array('isi_tb'=>$dt_tb,'footer_tb'=>$footer_tb); 
	}

	function getdtmenu403($idkec,$iddesa,$iddusun,$idrt,$kb){ 
		
        if(empty($idrt)){
		 $kd_wl=$this->getkdwl($idkec,$iddesa,$iddusun,$idrt,'','','id_unit_detail_idk');
        }else{
         $kd_wl=$this->getkdwl($idkec,$iddesa,$iddusun,$idrt); 	
        }
		
		$str_kb = "Kd_nonacptr IS ".($kb==1 ? 'NULL' : 'NOT NULL')." AND pus='1'";

		$this->arrayks();

		$arrjml = array();
        if(empty($idrt)){
		  $dt = new dt_unit_detail;              
		  $data = $dt->getdata("$kd_wl");  

	 	  $tb = new tb_gen('tbgen');
		  $tb->sql_from="vw_fam_indv";		
		  $tb->sql_select = "SUM(Kd_fammbrtyp=1) AS j_kk,
		                   COUNT(*) AS j_jiwa,
		                   SUM(Kd_fammbrtyp=1 AND (".$this->arr_ks['pra_s'].")) AS j_pra_s,
		                   SUM(Kd_fammbrtyp=1 AND (".$this->arr_ks['ks_1'].")) AS j_ks";                           
		}else{
          $tb = new tb_gen('tbgen');
		  $tb->sql_from="vw_fam_indv";		
		  $tb->sql_select = "kd_fam,COUNT(*) AS jml_jiwa,Kd_prosplvl"; 
		  $tb->sql_groupby = 'Kd_fam';
		  $tb->sql_orderby = 'Kd_fam';              
		  $data = $tb->getData("$kd_wl ($str_kb) AND (".$this->arr_ks['pra_s']." OR ".$this->arr_ks['ks_1'].") and (Kd_mutasi IS NULL)");

		  $tb_indv = new tb_gen('dbo_individu');  
		  $tb_indv->sql_select = "Nama";
		  $arrjml['jml_jiwa']=0;
		  $arrjml['pra']=0;
		  $arrjml['ks']=0;
		}

		$dt_tb=array();
		$i=1;
		
		$jml_pra=1;
		$jml_ks=1;

        if(!empty($data)){
			foreach($data as $row)
			{
				$tmp_dt_tb=array();			

				if(empty($idrt))
				{
				  $tmp_dt_tb[]=$i;
				  $tmp_dt_tb[]=$row['no_unit_detail'];    
				

				  $kd_wlq=$this->getkdwl(($idkec==0 ? $row['id_unit_detail'] : $idkec ),
				  ( (($idkec!=0) and ($iddesa == 0)) ? $row['id_unit_detail'] : $iddesa),
				  ( (($idkec!=0) and ($iddesa != 0) and ($iddusun==0)) ? $row['id_unit_detail']  : $iddusun),
				  ((($idkec!=0) and ($iddesa != 0) and ($iddusun!=0) and ($idrt==0)) ? $row['id_unit_detail']  : $idrt));          
				
				  $data1 = $tb->getData("$kd_wlq ($str_kb) AND (".$this->arr_ks['pra_s']." OR ".$this->arr_ks['ks_1'].") AND Kd_mutasi IS NULL");			
				  $rc = $this->build_rc($data1);
	            
	              $tmp_dt_tb[]=$this->frupiah($rc,'j_kk');
	              $arrjml['j_kk']=$this->fjml_ttl($arrjml,'j_kk',$rc,'j_kk');

	              $tmp_dt_tb[]=$this->frupiah($rc,'j_jiwa');
	              $arrjml['j_jiwa']=$this->fjml_ttl($arrjml,'j_jiwa',$rc,'j_jiwa');
	            
	              $tmp_dt_tb[]=$this->frupiah($rc,'j_pra_s');
	              $arrjml['j_pra_s']=$this->fjml_ttl($arrjml,'j_pra_s',$rc,'j_pra_s');            
	            
	              $tmp_dt_tb[]=$this->frupiah($rc,'j_ks');
	              $arrjml['j_ks']=$this->fjml_ttl($arrjml,'j_ks',$rc,'j_ks'); 
	            } else{
	            	$tmp_dt_tb[]=$row['Kd_fam'];
	               
	                $data1 = $tb_indv->getData("Kd_fam='$row[Kd_fam]' and Kd_fammbrtyp=1");			
				    $rc = $this->build_rc($data1);     

				    $tmp_dt_tb[]=$rc['Nama'];
				    $tmp_dt_tb[]=$row['jml_jiwa'];
				    $arrjml['jml_jiwa']=$this->fjml_ttl($arrjml,'jml_jiwa',$row,'jml_jiwa');
				    
				    if(($row['Kd_prosplvl']==1) or ($row['Kd_prosplvl']==6)){
				      $tmp_dt_tb[]='V';
				      $arrjml['pra'] = $this->fjml_ttl($arrjml,'pra',$jml_pra,'');
				    }else{
				      $tmp_dt_tb[]=' ';
				    }

				    if(($row['Kd_prosplvl']==2) or ($row['Kd_prosplvl']==7)){
				      $tmp_dt_tb[]='V';
				      $arrjml['ks'] = $this->fjml_ttl($arrjml,'ks',$jml_ks,'');
				    }else{
				      $tmp_dt_tb[]=' ';
				    } 
	            }           

				$dt_tb[] = $tmp_dt_tb;
				$i++;
			}	
		}
		
		$footer_tb=array();
		$tmp_footer=array();       

		foreach ($arrjml as $key=>$value) {
			$tmp_footer[]= number_format($value,0,',','.');     
		}           

		$footer_tb[] = $tmp_footer;          
		
		return array('isi_tb'=>$dt_tb,'footer_tb'=>$footer_tb); 
	} 

	function getdtmenu404($idkec,$iddesa,$iddusun,$idrt,$kb,$ks){ 
		
        if(empty($idrt)){
		 $kd_wl=$this->getkdwl($idkec,$iddesa,$iddusun,$idrt,'','','id_unit_detail_idk');
        }else{
         $kd_wl=$this->getkdwl($idkec,$iddesa,$iddusun,$idrt); 	
        }

		if($kb<3){  
		  $str_kb = "Kd_nonacptr IS ".($kb==1 ? 'NULL' : 'NOT NULL')." AND pus='1'";
        }
		$this->arrayks();

		$tb_contr = new tb_gen('dbo_contr_typ');
		$dt_contr = $tb_contr->getData('');  

		if(!empty($dt_contr)){
			$str='';
			if($kb==1 and $ks==1){
			  foreach ($dt_contr as $row) {
				$str=(!empty($str) ? $str.',':'') ."SUM(Kd_contyp=$row[Kd_contyp] and Kd_fammbrtyp=1) AS j_$row[Kd_contyp]";
			  }
			}else{
			  foreach ($dt_contr as $row) {
				$str=(!empty($str) ? $str.',':'') ."SUM(Kd_contyp=$row[Kd_contyp] and 
				                                        Kd_fammbrtyp=1 and (".$this->arr_ks['pra_s'].")) 
				                                        AS j_$row[Kd_contyp]_pra_s";
			  }
			  foreach ($dt_contr as $row) {
				$str=(!empty($str) ? $str.',':'') ."SUM(Kd_contyp=$row[Kd_contyp] and 
				                                        Kd_fammbrtyp=1 and (".$this->arr_ks['ks_1'].")) 
				                                        AS j_$row[Kd_contyp]_ks";
			  }	
			}  
		} 

		$arrjml = array();
		
        if(empty($idrt)){
          $arrjml['j_kk']=0;
		  $arrjml['j_jiwa']=0;
          	
		  $dt = new dt_unit_detail;              
		  $data = $dt->getdata("$kd_wl"); 

		  $tb = new tb_gen('tbgen');
		  $tb->sql_from="vw_fam_indv"; 

		  switch($ks)
		  {
		  	case 1 : switch($kb)
		  	         {
		  	         	case 1 : $tb->sql_select = "SUM(Kd_fammbrtyp=1) AS j_kk,
								                   COUNT(*) AS j_jiwa,$str";
		  	         	         break;
		  	         	case 2 : $tb->sql_select = "SUM(Kd_fammbrtyp=1) AS j_kk,
								                   COUNT(*) AS j_jiwa,sum($str_kb and Kd_fammbrtyp=1) as j_pus";
		  	         	         break;
		  	         	case 3 : $tb->sql_select = "SUM(Kd_fammbrtyp=1) AS j_kk,
								                    COUNT(*) AS j_jiwa,
								                    SUM(pus='1' AND Kd_fammbrtyp=1) AS j_pus,
								                    SUM(pus='1' AND Kd_nonacptr IS NULL  AND Kd_fammbrtyp=1) AS j_kb,
								                    SUM(pus='1' AND Kd_nonacptr IS NOT NULL  AND Kd_fammbrtyp=1) AS j_nonkb ";
		  	         	         break;
		  	         }
		  	         break;
		  	case 2 : switch($kb)
		  	         {
		  	         	case 1 : $tb->sql_select = "SUM(Kd_fammbrtyp=1) AS j_kk,
								                   COUNT(*) AS j_jiwa,$str";
								 break;
		  	         	case 2 :  		
								  $tb->sql_select = "SUM(Kd_fammbrtyp=1) AS j_kk,
								                   COUNT(*) AS j_jiwa,
								                   SUM(Kd_fammbrtyp=1 AND (".$this->arr_ks['pra_s'].")) AS j_pra_s,
								                   SUM(Kd_fammbrtyp=1 AND (".$this->arr_ks['ks_1'].")) AS j_ks";
		  	         	         break;
		  	         	case 3 : $tb->sql_select = "SUM(Kd_fammbrtyp=1) AS j_kk,
								                   COUNT(*) AS j_jiwa,
								                   SUM(pus='1' AND Kd_fammbrtyp=1) AS j_pus,
								                   SUM(pus='1' AND Kd_nonacptr IS NULL AND Kd_fammbrtyp=1 AND (".$this->arr_ks['pra_s'].")) AS j_pra_s_kb,
								                   SUM(pus='1' AND Kd_nonacptr IS NULL AND Kd_fammbrtyp=1 AND (".$this->arr_ks['ks_1'].")) AS j_ks_kb,
								                   SUM(pus='1' AND Kd_nonacptr IS not NULL AND Kd_fammbrtyp=1 AND (".$this->arr_ks['pra_s'].")) AS j_pra_s_nonkb,
								                   SUM(pus='1' AND Kd_nonacptr IS not NULL AND Kd_fammbrtyp=1 AND (".$this->arr_ks['ks_1'].")) AS j_ks_nonkb";
								 break;
		  	         }
		  	         break;
		  }

	 	                            
		}else{
          $arrjml['j_jiwa']=0;

          $tb = new tb_gen('tbgen');
		  $tb->sql_from="vw_fam_indv";		   
		  $tb->sql_groupby = 'Kd_fam';
		  $tb->sql_orderby = 'Kd_fam';

          $tb_indv = new tb_gen('dbo_individu');  
		  $tb_indv->sql_select = "Nama";

          switch($ks)
		  {
		  	case 1 : switch($kb)
		  	         {
		  	         	case 1 : $tb->sql_select = "kd_fam,COUNT(*) AS j_jiwa,Kd_contyp";
		  	         	         $data = $tb->getData("$kd_wl ($str_kb) and (Kd_mutasi IS NULL)");
		  	         	         break;
		  	         	case 2 : $tb->sql_select = "kd_fam,COUNT(*) AS j_jiwa,pus";
		  	         	         $data = $tb->getData("$kd_wl (Kd_nonacptr IS NOT NULL OR (Kd_nonacptr IS NULL AND pus='0')) and (Kd_mutasi IS NULL)");
		  	         	         break;
		  	         	case 3 : $tb->sql_select = "kd_fam,COUNT(*) AS j_jiwa,pus,Kd_nonacptr";
		  	         	         $data = $tb->getData("$kd_wl (Kd_mutasi IS NULL)");
		  	         	         $arrjml['pus']=0;
		                         $arrjml['kb']=0;
		                         $arrjml['nonkb']=0;		                         
		  	         	         break;
		  	         }
		  	         break;
		  	case 2 : switch($kb)
		  	         {
		  	         	case 1 : $tb->sql_select = "kd_fam,COUNT(*) AS j_jiwa,Kd_prosplvl,Kd_contyp";
		  	         	         $data = $tb->getData("$kd_wl ($str_kb) AND (".$this->arr_ks['pra_s']." OR ".$this->arr_ks['ks_1'].") and (Kd_mutasi IS NULL)");

		  	         	         break;
		  	         	case 2 : $tb->sql_select = "kd_fam,COUNT(*) AS j_jiwa,Kd_prosplvl";
		  	         	         $data = $tb->getData("$kd_wl ($str_kb) AND (".$this->arr_ks['pra_s']." OR ".$this->arr_ks['ks_1'].") and (Kd_mutasi IS NULL)");	  
		                         
		                         $arrjml['pra']=0;
		                         $arrjml['ks']=0;
		  	         	         break;
		  	         	case 3 : $tb->sql_select = "kd_fam,COUNT(*) AS j_jiwa,Kd_fammbrtyp,pus,Kd_prosplvl,Kd_nonacptr";
		  	         	         $data = $tb->getData("$kd_wl (".$this->arr_ks['pra_s']." OR ".$this->arr_ks['ks_1'].") and (Kd_mutasi IS NULL)");
                                 $arrjml['pus']=0;
		  	         	         $arrjml['pra_kb']=0;
		                         $arrjml['ks_kb']=0;
		                         $arrjml['pra_nonkb']=0;
		                         $arrjml['ks_nonkb']=0;
		  	         	         break;
		  	         }
		  	         break;
		  }


                        
		  
		}

		$dt_tb=array();
		$i=1;
		
		$jml_pra=1;
		$jml_ks=1;

        if(!empty($data))
        {
			foreach($data as $row)
			{
				$tmp_dt_tb=array();			

				if(empty($idrt))
				{
				  $tmp_dt_tb[]=$i;
				  $tmp_dt_tb[]=$row['no_unit_detail'];

				  $kd_wlq=$this->getkdwl(($idkec==0 ? $row['id_unit_detail'] : $idkec ),
				  ( (($idkec!=0) and ($iddesa == 0)) ? $row['id_unit_detail'] : $iddesa),
				  ( (($idkec!=0) and ($iddesa != 0) and ($iddusun==0)) ? $row['id_unit_detail']  : $iddusun),
				  ((($idkec!=0) and ($iddesa != 0) and ($iddusun!=0) and ($idrt==0)) ? $row['id_unit_detail']  : $idrt));
	              
				  switch($ks)
				  {
				  	case 1 : switch($kb)
				  	         {
				  	         	case 1 :  
				  	         	          $data1 = $tb->getData("$kd_wlq ($str_kb) and Kd_mutasi IS NULL");			
										  $rc = $this->build_rc($data1);
							            
							              $tmp_dt_tb[]=$this->frupiah($rc,'j_kk');
							              $arrjml['j_kk']=$this->fjml_ttl($arrjml,'j_kk',$rc,'j_kk');

							              $tmp_dt_tb[]=$this->frupiah($rc,'j_jiwa');
							              $arrjml['j_jiwa']=$this->fjml_ttl($arrjml,'j_jiwa',$rc,'j_jiwa');

							              if(!empty($dt_contr)){
												$jml=0;
												foreach ($dt_contr as $row) {
													$j_contyp="j_$row[Kd_contyp]";
													$tmp_dt_tb[]=$this->frupiah($rc,$j_contyp);
							                        $arrjml[$j_contyp]=$this->fjml_ttl($arrjml,$j_contyp,$rc,$j_contyp);
							                        $jml=$this->fjml_ttl($jml,'',$rc,$j_contyp);				
												}
												$tmp_dt_tb[]=number_format($jml,0,',','.');
												$arrjml['ttl']=$this->fjml_ttl($arrjml,'ttl',$jml,'');
											} 

				  	         	         break;
				  	         	case 2 : $data1 = $tb->getData("$kd_wlq (Kd_nonacptr IS NOT NULL OR (Kd_nonacptr IS NULL AND pus='0')) AND Kd_mutasi IS NULL");			
										  $rc = $this->build_rc($data1);
							            
							              $tmp_dt_tb[]=$this->frupiah($rc,'j_kk');
							              $arrjml['j_kk']=$this->fjml_ttl($arrjml,'j_kk',$rc,'j_kk');

							              $tmp_dt_tb[]=$this->frupiah($rc,'j_jiwa');
							              $arrjml['j_jiwa']=$this->fjml_ttl($arrjml,'j_jiwa',$rc,'j_jiwa');

							              $tmp_dt_tb[]=$this->frupiah($rc,'j_pus');
							              $arrjml['j_pus']=$this->fjml_ttl($arrjml,'j_pus',$rc,'j_pus');
							              break;
				  	         	case 3 : $data1 = $tb->getData("$kd_wlq Kd_mutasi IS NULL");			
										  $rc = $this->build_rc($data1);
							            
							              $tmp_dt_tb[]=$this->frupiah($rc,'j_kk');
							              $arrjml['j_kk']=$this->fjml_ttl($arrjml,'j_kk',$rc,'j_kk');

							              $tmp_dt_tb[]=$this->frupiah($rc,'j_jiwa');
							              $arrjml['j_jiwa']=$this->fjml_ttl($arrjml,'j_jiwa',$rc,'j_jiwa');

							              $tmp_dt_tb[]=$this->frupiah($rc,'j_pus');
							              $arrjml['j_pus']=$this->fjml_ttl($arrjml,'j_pus',$rc,'j_pus');

							              $tmp_dt_tb[]=$this->frupiah($rc,'j_kb');
							              $arrjml['j_kb']=$this->fjml_ttl($arrjml,'j_kb',$rc,'j_kb');

							              $tmp_dt_tb[]=$this->frupiah($rc,'j_nonkb');
							              $arrjml['j_nonkb']=$this->fjml_ttl($arrjml,'j_nonkb',$rc,'j_nonkb');
							              break;
				  	         }
				  	         break;
				  	case 2 : switch($kb)
				  	         {
				  	         	case 1 : 
				  	         	          $data1 = $tb->getData("$kd_wlq ($str_kb) AND Kd_mutasi IS NULL");			
										  $rc = $this->build_rc($data1);
							            
							              $tmp_dt_tb[]=$this->frupiah($rc,'j_kk');
							              $arrjml['j_kk']=$this->fjml_ttl($arrjml,'j_kk',$rc,'j_kk');

							              $tmp_dt_tb[]=$this->frupiah($rc,'j_jiwa');
							              $arrjml['j_jiwa']=$this->fjml_ttl($arrjml,'j_jiwa',$rc,'j_jiwa');

							              if(!empty($dt_contr)){
												$jml=0;
												foreach ($dt_contr as $row) {
													$j_contyp="j_$row[Kd_contyp]_pra_s";
													$tmp_dt_tb[]=$this->frupiah($rc,$j_contyp);
							                        $arrjml[$j_contyp]=$this->fjml_ttl($arrjml,$j_contyp,$rc,$j_contyp);
							                        $jml=$this->fjml_ttl($jml,'',$rc,$j_contyp);				
												}
												$tmp_dt_tb[]=number_format($jml,0,',','.');
												$arrjml['ttl']=$this->fjml_ttl($arrjml,'ttl',$jml,'');

												$jml=0;
												foreach ($dt_contr as $row) {
													$j_contyp="j_$row[Kd_contyp]_ks";
													$tmp_dt_tb[]=$this->frupiah($rc,$j_contyp);
							                        $arrjml[$j_contyp]=$this->fjml_ttl($arrjml,$j_contyp,$rc,$j_contyp);
							                        $jml=$this->fjml_ttl($jml,'',$rc,$j_contyp);				
												}
												$tmp_dt_tb[]=number_format($jml,0,',','.');
												$arrjml['ttl1']=$this->fjml_ttl($arrjml,'ttl1',$jml,'');
											} 

				  	         	          break;
				  	         	case 2 :  
				  	         	          $data1 = $tb->getData("$kd_wlq ($str_kb) AND (".$this->arr_ks['pra_s']." OR ".$this->arr_ks['ks_1'].") AND Kd_mutasi IS NULL");			
										  $rc = $this->build_rc($data1);
							            
							              $tmp_dt_tb[]=$this->frupiah($rc,'j_kk');
							              $arrjml['j_kk']=$this->fjml_ttl($arrjml,'j_kk',$rc,'j_kk');

							              $tmp_dt_tb[]=$this->frupiah($rc,'j_jiwa');
							              $arrjml['j_jiwa']=$this->fjml_ttl($arrjml,'j_jiwa',$rc,'j_jiwa');
							            
							              $tmp_dt_tb[]=$this->frupiah($rc,'j_pra_s');
							              $arrjml['j_pra_s']=$this->fjml_ttl($arrjml,'j_pra_s',$rc,'j_pra_s');            
							            
							              $tmp_dt_tb[]=$this->frupiah($rc,'j_ks');
							              $arrjml['j_ks']=$this->fjml_ttl($arrjml,'j_ks',$rc,'j_ks'); 

				  	         	         break;
				  	         	case 3 :  
				  	         	          $data1 = $tb->getData("$kd_wlq (".$this->arr_ks['pra_s']." OR ".$this->arr_ks['ks_1'].") AND Kd_mutasi IS NULL");			
										  $rc = $this->build_rc($data1);
							            
							              $tmp_dt_tb[]=$this->frupiah($rc,'j_kk');
							              $arrjml['j_kk']=$this->fjml_ttl($arrjml,'j_kk',$rc,'j_kk');

							              $tmp_dt_tb[]=$this->frupiah($rc,'j_jiwa');
							              $arrjml['j_jiwa']=$this->fjml_ttl($arrjml,'j_jiwa',$rc,'j_jiwa');

							              $tmp_dt_tb[]=$this->frupiah($rc,'j_pus');
							              $arrjml['j_pus']=$this->fjml_ttl($arrjml,'j_pus',$rc,'j_pus');
							              
							              $tmp_dt_tb[]=$this->frupiah($rc,'j_pra_s_kb');
							              $arrjml['j_pra_s_kb']=$this->fjml_ttl($arrjml,'j_pra_s_kb',$rc,'j_pra_s_kb');

							              $tmp_dt_tb[]=$this->frupiah($rc,'j_ks_kb');
							              $arrjml['j_ks_kb']=$this->fjml_ttl($arrjml,'j_ks_kb',$rc,'j_ks_kb');

							              $tmp_dt_tb[]=$this->frupiah($this->fjml_ttl($rc,'j_pra_s_kb',$rc,'j_ks_kb'),'');
							              $arrjml['j_kb']=$this->fjml_ttl($arrjml,'j_kb',$this->fjml_ttl($rc,'j_pra_s_kb',$rc,'j_ks_kb'),'');

							              $tmp_dt_tb[]=$this->frupiah($rc,'j_pra_s_nonkb');
							              $arrjml['j_pra_s_nonkb']=$this->fjml_ttl($arrjml,'j_pra_s_nonkb',$rc,'j_pra_s_nonkb');

							              $tmp_dt_tb[]=$this->frupiah($rc,'j_ks_nonkb');
							              $arrjml['j_ks_nonkb']=$this->fjml_ttl($arrjml,'j_ks_nonkb',$rc,'j_ks_nonkb');

							              $tmp_dt_tb[]=$this->frupiah($this->fjml_ttl($rc,'j_pra_s_nonkb',$rc,'j_ks_nonkb'),'');
							              $arrjml['j_nonkb']=$this->fjml_ttl($arrjml,'j_nonkb',$this->fjml_ttl($rc,'j_pra_s_nonkb',$rc,'j_ks_nonkb'),'');

				  	         	         break;
				  	         }
				  	         break;
				  }    
				

				            
				
				  
	            } else{
	            	
	            	   $tmp_dt_tb[]=$row['Kd_fam'];
	               
	                   $data1 = $tb_indv->getData("Kd_fam='$row[Kd_fam]' and Kd_fammbrtyp=1");			
				       $rc = $this->build_rc($data1); 

				       $tmp_dt_tb[]=$rc['Nama'];

				       $tmp_dt_tb[]=$row['j_jiwa'];
				       $arrjml['j_jiwa']=$this->fjml_ttl($arrjml,'j_jiwa',$row,'j_jiwa');


	            	   switch($ks)
					  {
					  	case 1 : switch($kb)
					  	         {
					  	         	case 1 : if(!empty($dt_contr)){
												
												foreach ($dt_contr as $row1) {
													$tmp_dt_tb[]= $row1['Kd_contyp']== $row['Kd_contyp'] ? 'V' : '';
													$arrjml[$row1['Kd_contyp']] = $this->fjml_ttl($arrjml,$row1['Kd_contyp'],$row1['Kd_contyp']== $row['Kd_contyp'] ? 1 : 0,'');
												}
												
											} 
					  	         	         break;
					  	         	case 2 : 
	                                         $tmp_dt_tb[]= $row['pus']==1 ? 'V' : '';
	                                         $arrjml['pus'] = $this->fjml_ttl($arrjml,'pus',$row['pus']==1 ? 1 : 0,'');
					  	         	         break;
					  	         	case 3 : $tmp_dt_tb[]= $row['pus']==1 ? 'V' : '';
	                                         $arrjml['pus'] = $this->fjml_ttl($arrjml,'pus',$row['pus']==1 ? 1 : 0,'');

	                                         if($row['Kd_nonacptr']!=NULL)
	                                         {
	                                             $tmp_dt_tb[]= '';                                             
	                                             $tmp_dt_tb[]= 'V';
	                                             $arrjml['nonkb'] = $this->fjml_ttl($arrjml,'nonkb',1,'');
	                                         }else if($row['Kd_nonacptr']==NULL AND $row['pus']==0){
	                                             $tmp_dt_tb[]= '';                                             
	                                             $tmp_dt_tb[]= 'V';
	                                             $arrjml['nonkb'] = $this->fjml_ttl($arrjml,'nonkb',1,'');
	                                         }else{
	                                         	 $tmp_dt_tb[]= 'V';
	                                         	 $arrjml['kb'] = $this->fjml_ttl($arrjml,'kb',1,'');
	                                         	 $tmp_dt_tb[]= '';
	                                         }
					  	         	         break;
					  	         }
					  	         break;
					  	case 2 : switch($kb)
					  	         {
					  	         	case 1 : if(!empty($dt_contr)){
												
												foreach ($dt_contr as $row1) {
													$tmp_dt_tb[]= (($row['Kd_prosplvl']==1 or $row['Kd_prosplvl']==6) and ($row1['Kd_contyp']== $row['Kd_contyp'])) ? 'V' : '';
													$arrjml[$row1['Kd_contyp'].'_pra_s'] = $this->fjml_ttl($arrjml,$row1['Kd_contyp'].'_pra_s',
														((($row['Kd_prosplvl']==1 or $row['Kd_prosplvl']==6) and ($row1['Kd_contyp']== $row['Kd_contyp'])) ? 1 : 0),'');
												}

												foreach ($dt_contr as $row1) {
													$tmp_dt_tb[]= (($row['Kd_prosplvl']==2 or $row['Kd_prosplvl']==7) and ($row1['Kd_contyp']== $row['Kd_contyp'])) ? 'V' : '';
													$arrjml[$row1['Kd_contyp'].'_ks'] = $this->fjml_ttl($arrjml,$row1['Kd_contyp'].'_ks',
														((($row['Kd_prosplvl']==2 or $row['Kd_prosplvl']==7) and ($row1['Kd_contyp']== $row['Kd_contyp'])) ? 1 : 0),'');
												}
												
											} 
					  	         	         break;
					  	         	case 2 :    if(($row['Kd_prosplvl']==1) or ($row['Kd_prosplvl']==6)){
											      $tmp_dt_tb[]='V';
											      $arrjml['pra'] = $this->fjml_ttl($arrjml,'pra',$jml_pra,'');
											    }else{
											      $tmp_dt_tb[]=' ';
											    }

											    if(($row['Kd_prosplvl']==2) or ($row['Kd_prosplvl']==7)){
											      $tmp_dt_tb[]='V';
											      $arrjml['ks'] = $this->fjml_ttl($arrjml,'ks',$jml_ks,'');
											    }else{
											      $tmp_dt_tb[]=' ';
											    } 

					  	         	         break;
					  	         	case 3 :   
	                                            if($row['pus']==1)
	                                            {
	                                              $tmp_dt_tb[]='V';
											      $arrjml['pus'] = $this->fjml_ttl($arrjml,'pus',1,'');
	                                            } else{
	                                              $tmp_dt_tb[]=' ';
	                                            }
					  	         	            
					  	         	            if(($row['pus']==1) and ($row['Kd_nonacptr']==null) and (($row['Kd_prosplvl']==1) or ($row['Kd_prosplvl']==6))){
											       $tmp_dt_tb[]='V';
											       $arrjml['pra_kb'] = $this->fjml_ttl($arrjml,'pra_kb',1,'');
											    }else{
											       $tmp_dt_tb[]=' ';
											    }

											    if(($row['pus']==1) and ($row['Kd_nonacptr']==null) and (($row['Kd_prosplvl']==2) or ($row['Kd_prosplvl']==7))){
											      $tmp_dt_tb[]='V';
											      $arrjml['ks_kb'] = $this->fjml_ttl($arrjml,'ks_kb',1,'');
											    }else{
											      $tmp_dt_tb[]=' ';
											    } 

											    if(($row['pus']==1) and ($row['Kd_nonacptr']!=null) and (($row['Kd_prosplvl']==1) or ($row['Kd_prosplvl']==6))){
											       $tmp_dt_tb[]='V';
											       $arrjml['pra_nonkb'] = $this->fjml_ttl($arrjml,'pra_nonkb',1,'');
											    }else{
											       $tmp_dt_tb[]=' ';
											    }

											    if(($row['pus']==1) and ($row['Kd_nonacptr']!=null) and (($row['Kd_prosplvl']==2) or ($row['Kd_prosplvl']==7))){
											      $tmp_dt_tb[]='V';
											      $arrjml['ks_nonkb'] = $this->fjml_ttl($arrjml,'ks_nonkb',1,'');
											    }else{
											      $tmp_dt_tb[]=' ';
											    } 

					  	         	         break;
					  	         }
					  	         break;
					  }


	            	
				    
				    
				    
	            }           

				$dt_tb[] = $tmp_dt_tb;
				$i++;
			}	
		}
		
		$footer_tb=array();
		$tmp_footer=array();       

		foreach ($arrjml as $key=>$value) {
			$tmp_footer[]= number_format($value,0,',','.');     
		}           

		$footer_tb[] = $tmp_footer;          
		
		return array('isi_tb'=>$dt_tb,'footer_tb'=>$footer_tb); 
	} 

	function getdtmenu02($idkec,$iddesa,$iddusun,$idrt){ 
		
        if(empty($idrt)){
		 $kd_wl=$this->getkdwl($idkec,$iddesa,$iddusun,$idrt,'','','id_unit_detail_idk');
        }else{
         $kd_wl=$this->getkdwl($idkec,$iddesa,$iddusun,$idrt); 	
        }
		
		$tb_contr = new tb_gen('dbo_contr_typ');
		$dt_contr = $tb_contr->getData('');  

		if(!empty($dt_contr)){
			$str='';
			  foreach ($dt_contr as $row) {
				$str=(!empty($str) ? $str.',':'') ."SUM(Kd_contyp=$row[Kd_contyp]) AS j_$row[Kd_contyp]";
			  }			  
		}

		$arrjml = array();
        if(empty($idrt)){
		  $dt = new dt_unit_detail;              
		  $data = $dt->getdata("$kd_wl");  

	 	  $tb = new tb_gen('dbo_family');
		  //$tb->sql_from="vw_fam_indv";		
		  $tb->sql_select = "count(*) AS j_kk,SUM(pus='1') AS j_pus,$str";                           
		}else{
          $tb = new tb_gen('tbgen');
		  $tb->sql_from="vw_fam_indv";		
		  $tb->sql_select = "kd_fam,COUNT(*) AS jml_jiwa,pus,Kd_contyp"; 
		  $tb->sql_groupby = 'Kd_fam';
		  $tb->sql_orderby = 'Kd_fam';              
		  $data = $tb->getData("$kd_wl (Kd_mutasi IS NULL)");

		  $tb_indv = new tb_gen('dbo_individu');  
		  $tb_indv->sql_select = "Nama";
		  $arrjml['jml_jiwa']=0;
          $arrjml['j_pus']=0;
          if(!empty($dt_contr)){                 			     
			     foreach ($dt_contr as $row) {
				   $str="j_$row[Kd_contyp]";			       
                   $arrjml[$str]=0;                   	   
			     }
		      }

		}

		$dt_tb=array();
		$i=1;
		
		$jml_pra=1;
		$jml_ks=1;

        if(!empty($data)){
			foreach($data as $row)
			{
				$tmp_dt_tb=array();			

				if(empty($idrt))
				{
				  $tmp_dt_tb[]=$i;
				  $tmp_dt_tb[]=$row['no_unit_detail'];    
				

				  $kd_wlq=$this->getkdwl(($idkec==0 ? $row['id_unit_detail'] : $idkec ),
				  ( (($idkec!=0) and ($iddesa == 0)) ? $row['id_unit_detail'] : $iddesa),
				  ( (($idkec!=0) and ($iddesa != 0) and ($iddusun==0)) ? $row['id_unit_detail']  : $iddusun),
				  ((($idkec!=0) and ($iddesa != 0) and ($iddusun!=0) and ($idrt==0)) ? $row['id_unit_detail']  : $idrt),'','');          
				
				  $data1 = $tb->getData("$kd_wlq");			
				  $rc = $this->build_rc($data1);
	            
	              $tmp_dt_tb[]=$this->frupiah($rc,'j_kk');
	              $arrjml['j_kk']=$this->fjml_ttl($arrjml,'j_kk',$rc,'j_kk');

	              $tmp_dt_tb[]=$this->frupiah($rc,'j_pus');
	              $arrjml['j_pus']=$this->fjml_ttl($arrjml,'j_pus',$rc,'j_pus');
	              
	              if(!empty($dt_contr)){
	                 $jml = 0;			     
				     foreach ($dt_contr as $row) {
					   $str="j_$row[Kd_contyp]";
				       $tmp_dt_tb[]=$this->frupiah($rc,$str);
	                   $arrjml[$str]=$this->fjml_ttl($arrjml,$str,$rc,$str);
	                   $jml=$this->fjml_ttl($jml,'',$rc,$str);	   
				     }
	                   $tmp_dt_tb[]=number_format($jml,0,',','.');
	                   $arrjml['jml']=$this->fjml_ttl($arrjml,'jml',$jml,'');
	                   $tmp_dt_tb[]=number_format($this->fprosen($jml,'',$rc,'j_pus'),2,',','.').'%';
			      }
	            
	               
	            } else{
	            	$tmp_dt_tb[]=$row['Kd_fam'];
	               
	                $data1 = $tb_indv->getData("Kd_fam='$row[Kd_fam]' and Kd_fammbrtyp=1");			
				    $rc = $this->build_rc($data1);     

				    $tmp_dt_tb[]=$rc['Nama'];
				    $tmp_dt_tb[]=$row['jml_jiwa'];
				    $arrjml['jml_jiwa']=$this->fjml_ttl($arrjml,'jml_jiwa',$row,'jml_jiwa');
				    
				    if($row['pus']==1)
				    {
	                  $tmp_dt_tb[]='V';
				      $arrjml['j_pus']=$this->fjml_ttl($arrjml['j_pus'],'',1,'');
				    }else{
				    	$tmp_dt_tb[]='';
				    }

				    if(!empty($dt_contr)){                 			     
				     foreach ($dt_contr as $row1) {
					    if($row['Kd_contyp']==$row1['Kd_contyp'])
					    {
	                      $tmp_dt_tb[]='V';
	                      $str="j_$row1[Kd_contyp]";
				          $arrjml[$str]=$this->fjml_ttl($arrjml[$str],'',1,'');
					    } else{
					    	$tmp_dt_tb[]='';
					    }                	   
				     }
			      }
				     
	            }           

				$dt_tb[] = $tmp_dt_tb;
				$i++;
			}	
		}
		
		$footer_tb=array();
		$tmp_footer=array();

		if(empty($idrt))
		{
            $arrjml['prosen']=$this->fprosen($arrjml,'jml',$arrjml,'j_pus');
		}       

		foreach ($arrjml as $key=>$value) {
			$tmp_footer[]= $key=='prosen' ? number_format($value,2,',','.').'%' : number_format($value,0,',','.');     
		}           

		$footer_tb[] = $tmp_footer;          
		
		return array('isi_tb'=>$dt_tb,'footer_tb'=>$footer_tb); 
	}

	function getdtmenu421($idkec,$iddesa,$iddusun,$idrt){ 
		
        if(empty($idrt)){
		 $kd_wl=$this->getkdwl($idkec,$iddesa,$iddusun,$idrt,'','','id_unit_detail_idk');
        }else{
         $kd_wl=$this->getkdwl($idkec,$iddesa,$iddusun,$idrt); 	
        }
		
		
		$arrjml = array();
        if(empty($idrt)){
		  $dt = new dt_unit_detail;              
		  $data = $dt->getdata("$kd_wl");  

	 	  $tb = new tb_gen('tbgen');
		  $tb->sql_from="vw_fam_indv";		
		  $tb->sql_select = "sum(Kd_fammbrtyp=1) AS j_kk,
		                         sum(kd_gen=1) as j_l,
		                         sum(kd_gen=2) as j_p,
		                         count(*) as jml";                           
		}else{
          $tb = new tb_gen('tbgen');
		  $tb->sql_from="vw_fam_indv";		
		  $tb->sql_select = "kd_fam,sum(kd_gen=1) as j_l,sum(kd_gen=2) as j_p,count(*) as jml"; 
		  $tb->sql_groupby = 'Kd_fam';
		  $tb->sql_orderby = 'Kd_fam';              
		  $data = $tb->getData("$kd_wl (Kd_mutasi IS NULL)");

		  $tb_indv = new tb_gen('dbo_individu');  
		  $tb_indv->sql_select = "Nama";
		     

		}

		$dt_tb=array();
		$i=1;
		
		$jml_pra=1;
		$jml_ks=1;

        if(!empty($data)){ 
			foreach($data as $row)
			{
				$tmp_dt_tb=array();			

				if(empty($idrt))
				{
				  $tmp_dt_tb[]=$i;
				  $tmp_dt_tb[]=$row['no_unit_detail'];    
				

				  $kd_wlq=$this->getkdwl(($idkec==0 ? $row['id_unit_detail'] : $idkec ),
				  ( (($idkec!=0) and ($iddesa == 0)) ? $row['id_unit_detail'] : $iddesa),
				  ( (($idkec!=0) and ($iddesa != 0) and ($iddusun==0)) ? $row['id_unit_detail']  : $iddusun),
				  ((($idkec!=0) and ($iddesa != 0) and ($iddusun!=0) and ($idrt==0)) ? $row['id_unit_detail']  : $idrt));          
				
				  $data1 = $tb->getData("$kd_wlq Kd_mutasi IS NULL");			
				  $rc = $this->build_rc($data1);
	            
	              $tmp_dt_tb[]=$this->frupiah($rc,'j_kk');
	              $arrjml['j_kk']=$this->fjml_ttl($arrjml,'j_kk',$rc,'j_kk');

	              $tmp_dt_tb[]=$this->frupiah($rc,'j_l');
	              $arrjml['j_l']=$this->fjml_ttl($arrjml,'j_l',$rc,'j_l');

	              $tmp_dt_tb[]=$this->frupiah($rc,'j_p');
	              $arrjml['j_p']=$this->fjml_ttl($arrjml,'j_p',$rc,'j_p');

	              $tmp_dt_tb[]=$this->frupiah($rc,'jml');
	              $arrjml['jml']=$this->fjml_ttl($arrjml,'jml',$rc,'jml');
	           
	               
	            } else{
	            	$tmp_dt_tb[]=$row['Kd_fam'];
	               
	                $data1 = $tb_indv->getData("Kd_fam='$row[Kd_fam]' and Kd_fammbrtyp=1");			
				    $rc = $this->build_rc($data1);     

				    $tmp_dt_tb[]=$rc['Nama'];
				    
				    $tmp_dt_tb[]=number_format($row['j_l'],0,',','.');
	                $arrjml['j_l']=$this->fjml_ttl($arrjml,'j_l',$row,'j_l');

	                $tmp_dt_tb[]=number_format($row['j_p'],0,',','.');
	                $arrjml['j_p']=$this->fjml_ttl($arrjml,'j_p',$row,'j_p');

	                $tmp_dt_tb[]=number_format($row['jml'],0,',','.');
	                $arrjml['jml']=$this->fjml_ttl($arrjml,'jml',$row,'jml');		   
				     
	            }           

				$dt_tb[] = $tmp_dt_tb;
				$i++;
			}	
		}
		
		$footer_tb=array();
		$tmp_footer=array();		       

		foreach ($arrjml as $key=>$value) {
			$tmp_footer[]= number_format($value,0,',','.');     
		}           

		$footer_tb[] = $tmp_footer;          
		
		return array('isi_tb'=>$dt_tb,'footer_tb'=>$footer_tb); 
	}

	function getdtmenu422($idkec,$iddesa,$iddusun,$idrt,$cmbumur,$dtumur){ 
		
        if(empty($idrt)){
		 $kd_wl=$this->getkdwl($idkec,$iddesa,$iddusun,$idrt,'','','id_unit_detail_idk');
        }else{
         $kd_wl=$this->getkdwl($idkec,$iddesa,$iddusun,$idrt); 	
        }
		
		switch($cmbumur)
		{
		case 1 : $umur = $this->getrentang($dtumur[0],$dtumur[0]);break;
		case 2 : $umur = $this->getrentang(0,$dtumur[0]-1);break;
		case 3 : $umur = $this->getrentang($dtumur[0]+1);break;
		case 4 : $umur = $this->getrentang($dtumur[0],$dtumur[1]);break; 
		}
		
		$arrjml = array();
        if(empty($idrt)){
		  $dt = new dt_unit_detail;              
		  $data = $dt->getdata("$kd_wl");  

	 	  $tb = new tb_gen('tbgen');
		  $tb->sql_from="vw_fam_indv";		
		  $tb->sql_select = "    sum(kd_gen=1) as j_l,
		                         sum(kd_gen=2) as j_p,
		                         count(*) as jml";                           
		}else{
          $tb = new tb_gen('tbgen');
		  $tb->sql_from="vw_fam_indv";		
		  $tb->sql_select = "*";		  
		  $tb->sql_orderby = 'Kd_fam';              
		  $data = $tb->getData("$kd_wl ($umur) and (Kd_mutasi IS NULL)");

		  $tb_gender = new tb_gen('dbo_gender');  
		  $tb_gender->sql_select = "Nm_gen_ind";

		  $tb_fammbrtyp = new tb_gen('dbo_fam_mbr_typ');  
		  $tb_fammbrtyp->sql_select = "Nm_fammbrtyp_ind";
		     

		}

		$dt_tb=array();
		$i=1;
		
		$jml_pra=1;
		$jml_ks=1;

        if(!empty($data)){
			foreach($data as $row)
			{
				$tmp_dt_tb=array();			

				if(empty($idrt))
				{
				  $tmp_dt_tb[]=$i;
				  $tmp_dt_tb[]=$row['no_unit_detail'];    
				

				  $kd_wlq=$this->getkdwl(($idkec==0 ? $row['id_unit_detail'] : $idkec ),
				  ( (($idkec!=0) and ($iddesa == 0)) ? $row['id_unit_detail'] : $iddesa),
				  ( (($idkec!=0) and ($iddesa != 0) and ($iddusun==0)) ? $row['id_unit_detail']  : $iddusun),
				  ((($idkec!=0) and ($iddesa != 0) and ($iddusun!=0) and ($idrt==0)) ? $row['id_unit_detail']  : $idrt));          
				
				  $data1 = $tb->getData("$kd_wlq ($umur) and Kd_mutasi IS NULL");			
				  $rc = $this->build_rc($data1);
	            
	              $tmp_dt_tb[]=$this->frupiah($rc,'j_l');
	              $arrjml['j_l']=$this->fjml_ttl($arrjml,'j_l',$rc,'j_l');

	              $tmp_dt_tb[]=$this->frupiah($rc,'j_p');
	              $arrjml['j_p']=$this->fjml_ttl($arrjml,'j_p',$rc,'j_p');

	              $tmp_dt_tb[]=$this->frupiah($rc,'jml');
	              $arrjml['jml']=$this->fjml_ttl($arrjml,'jml',$rc,'jml');
	           
	               
	            } else{
	            	$tmp_dt_tb[]=$row['kd_indv'];
	               
	                     

				    $tmp_dt_tb[]=$row['nama'];
				    
				    $data1 = $tb_gender->getData("Kd_gen=$row[kd_gen]");			
				    $rc = $this->build_rc($data1);

				    $tmp_dt_tb[]=$rc['Nm_gen_ind'];

	                $data1 = $tb_fammbrtyp->getData("Kd_fammbrtyp=$row[kd_fammbrtyp]");			
				    $rc = $this->build_rc($data1);

	                $tmp_dt_tb[]=$rc['Nm_fammbrtyp_ind'];
	                
	                $t=explode("-",$row[tgl_lahir]);
		            $tgl_lhr=$t[2]."-".$t[1]."-".$t[0]; 
	                $tmp_dt_tb[]=$tgl_lhr;
	                		   
				     
	            }           

				$dt_tb[] = $tmp_dt_tb;
				$i++;
			}	
		}	
		
		  $footer_tb=array();
		if(empty($idrt)){  
		  $tmp_footer=array();		       

		  foreach ($arrjml as $key=>$value) {
			$tmp_footer[]= number_format($value,0,',','.');     
		  }           

		  $footer_tb[] = $tmp_footer;          
		}
		return array('isi_tb'=>$dt_tb,'footer_tb'=>$footer_tb); 
	}

	function getdtmenu423($idkec,$iddesa,$iddusun,$idrt,$cmbumur,$dtumur,$cmbkerja){ 
		
        if(empty($idrt)){
		 $kd_wl=$this->getkdwl($idkec,$iddesa,$iddusun,$idrt,'','','id_unit_detail_idk');
        }else{
         $kd_wl=$this->getkdwl($idkec,$iddesa,$iddusun,$idrt); 	
        }
		
		switch($cmbumur)
		{
		case 1 : $umur = $this->getrentang($dtumur[0],$dtumur[0]);break;
		case 2 : $umur = $this->getrentang(0,$dtumur[0]-1);break;
		case 3 : $umur = $this->getrentang($dtumur[0]+1);break;
		case 4 : $umur = $this->getrentang($dtumur[0],$dtumur[1]);break; 
		}

		$str_krj = $cmbkerja == 1 ? 'Kd_emp!=6' : 'Kd_emp=6';
		
		$arrjml = array();
        if(empty($idrt)){
		  $dt = new dt_unit_detail;              
		  $data = $dt->getdata("$kd_wl");  

	 	  $tb = new tb_gen('tbgen');
		  $tb->sql_from="vw_fam_indv";		
		  $tb->sql_select = "    sum(kd_gen=1) as j_l,
		                         sum(kd_gen=2) as j_p,
		                         count(*) as jml";                           
		}else{
          $tb = new tb_gen('tbgen');
		  $tb->sql_from="vw_fam_indv";		
		  $tb->sql_select = "*";		  
		  $tb->sql_orderby = 'Kd_fam';              
		  $data = $tb->getData("$kd_wl ($umur) and ($str_krj) and (Kd_mutasi IS NULL)");

		  $tb_gender = new tb_gen('dbo_gender');  
		  $tb_gender->sql_select = "Nm_gen_ind";

		  $tb_fammbrtyp = new tb_gen('dbo_fam_mbr_typ');  
		  $tb_fammbrtyp->sql_select = "Nm_fammbrtyp_ind";
		     

		}

		$dt_tb=array();
		$i=1;
		
		$jml_pra=1;
		$jml_ks=1;

        if(!empty($data)){
			foreach($data as $row)
			{
				$tmp_dt_tb=array();			

				if(empty($idrt))
				{
				  $tmp_dt_tb[]=$i;
				  $tmp_dt_tb[]=$row['no_unit_detail'];    
				

				  $kd_wlq=$this->getkdwl(($idkec==0 ? $row['id_unit_detail'] : $idkec ),
				  ( (($idkec!=0) and ($iddesa == 0)) ? $row['id_unit_detail'] : $iddesa),
				  ( (($idkec!=0) and ($iddesa != 0) and ($iddusun==0)) ? $row['id_unit_detail']  : $iddusun),
				  ((($idkec!=0) and ($iddesa != 0) and ($iddusun!=0) and ($idrt==0)) ? $row['id_unit_detail']  : $idrt));          
				
				  $data1 = $tb->getData("$kd_wlq ($umur) and ($str_krj) and Kd_mutasi IS NULL");			
				  $rc = $this->build_rc($data1);
	            
	              $tmp_dt_tb[]=$this->frupiah($rc,'j_l');
	              $arrjml['j_l']=$this->fjml_ttl($arrjml,'j_l',$rc,'j_l');

	              $tmp_dt_tb[]=$this->frupiah($rc,'j_p');
	              $arrjml['j_p']=$this->fjml_ttl($arrjml,'j_p',$rc,'j_p');

	              $tmp_dt_tb[]=$this->frupiah($rc,'jml');
	              $arrjml['jml']=$this->fjml_ttl($arrjml,'jml',$rc,'jml');
	           
	               
	            } else{
	            	$tmp_dt_tb[]=$row['kd_indv'];                    

				    $tmp_dt_tb[]=$row['nama'];
				    
				    $data1 = $tb_gender->getData("Kd_gen=$row[kd_gen]");			
				    $rc = $this->build_rc($data1);

				    $tmp_dt_tb[]=$rc['Nm_gen_ind'];

	                $data1 = $tb_fammbrtyp->getData("Kd_fammbrtyp=$row[kd_fammbrtyp]");			
				    $rc = $this->build_rc($data1);

	                $tmp_dt_tb[]=$rc['Nm_fammbrtyp_ind'];
	                
	                $t=explode("-",$row[tgl_lahir]);
		            $tgl_lhr=$t[2]."-".$t[1]."-".$t[0]; 
	                $tmp_dt_tb[]=$tgl_lhr;
	                		   
				     
	            }           

				$dt_tb[] = $tmp_dt_tb;
				$i++;
			}	
		}
		
		  $footer_tb=array();
		if(empty($idrt)){  
		  $tmp_footer=array();		       

		  foreach ($arrjml as $key=>$value) {
			$tmp_footer[]= number_format($value,0,',','.');     
		  }           

		  $footer_tb[] = $tmp_footer;          
		}
		return array('isi_tb'=>$dt_tb,'footer_tb'=>$footer_tb); 
	}

	function getdtmenu424($idkec,$iddesa,$iddusun,$idrt,$cmbsekolah){ 
		
        if(empty($idrt)){
		 $kd_wl=$this->getkdwl($idkec,$iddesa,$iddusun,$idrt,'','','id_unit_detail_idk');
        }else{
         $kd_wl=$this->getkdwl($idkec,$iddesa,$iddusun,$idrt); 	
        }
		
		$str_712 = $this->getrentang(7,12);
		$str_1315 = $this->getrentang(13,15);
		$str_1618 = $this->getrentang(16,18);
		$str = $this->getrentang(7,18);

		$str_sekolah = $cmbsekolah == 1 ? 'Kd_edu!=0' : 'Kd_edu=0';
		
		$arrjml = array();
        if(empty($idrt)){
		  $dt = new dt_unit_detail;              
		  $data = $dt->getdata("$kd_wl");  

	 	  $tb = new tb_gen('tbgen');
		  $tb->sql_from="vw_fam_indv";		
		  $tb->sql_select = "sum(kd_gen=1 and ($str_712)) as j_l_712,
		                     sum(kd_gen=2 and ($str_712)) as j_p_712,
		                     sum($str_712) as jml_712,
		                     sum(kd_gen=1 and ($str_1315)) as j_l_1315,
		                     sum(kd_gen=2 and ($str_1315)) as j_p_1315,
		                     sum($str_1315) as jml_1315,
		                     sum(kd_gen=1 and ($str_1618)) as j_l_1618,
		                     sum(kd_gen=2 and ($str_1618)) as j_p_1618,
		                     sum($str_1618) as jml_1618,
		                     count(*) as jml";                           
		}else{
          $tb = new tb_gen('tbgen');
		  $tb->sql_from="vw_fam_indv";		
		  $tb->sql_select = "kd_indv,nama,kd_gen,tgl_lahir,
		                     if($str_712,1,0) as u712,
		                     if($str_1315,1,0) as u1315,
		                     if($str_1618,1,0) as u1618";		  
		  $tb->sql_orderby = 'Kd_fam';              
		  $data = $tb->getData("$kd_wl ($str) and ($str_sekolah) and (Kd_mutasi IS NULL)");

		  $tb_gender = new tb_gen('dbo_gender');  
		  $tb_gender->sql_select = "Nm_gen_ind";

		}

		$dt_tb=array();
		$i=1;
		
		$jml_pra=1;
		$jml_ks=1;

        if(!empty($data)){
			foreach($data as $row)
			{
				$tmp_dt_tb=array();			

				if(empty($idrt))
				{
				  $tmp_dt_tb[]=$i;
				  $tmp_dt_tb[]=$row['no_unit_detail'];    
				

				  $kd_wlq=$this->getkdwl(($idkec==0 ? $row['id_unit_detail'] : $idkec ),
				  ( (($idkec!=0) and ($iddesa == 0)) ? $row['id_unit_detail'] : $iddesa),
				  ( (($idkec!=0) and ($iddesa != 0) and ($iddusun==0)) ? $row['id_unit_detail']  : $iddusun),
				  ((($idkec!=0) and ($iddesa != 0) and ($iddusun!=0) and ($idrt==0)) ? $row['id_unit_detail']  : $idrt));          
				
				  $data1 = $tb->getData("$kd_wlq ($str_sekolah) and ($str) and Kd_mutasi IS NULL");			
				  $rc = $this->build_rc($data1);
	            
	              $tmp_dt_tb[]=$this->frupiah($rc,'j_l_712');
	              $arrjml['j_l_712']=$this->fjml_ttl($arrjml,'j_l_712',$rc,'j_l_712');

	              $tmp_dt_tb[]=$this->frupiah($rc,'j_p_712');
	              $arrjml['j_p_712']=$this->fjml_ttl($arrjml,'j_p_712',$rc,'j_p_712');

	              $tmp_dt_tb[]=$this->frupiah($rc,'jml_712');
	              $arrjml['jml_712']=$this->fjml_ttl($arrjml,'jml_712',$rc,'jml_712');

	              $tmp_dt_tb[]=$this->frupiah($rc,'j_l_1315');
	              $arrjml['j_l_1315']=$this->fjml_ttl($arrjml,'j_l_1315',$rc,'j_l_1315');

	              $tmp_dt_tb[]=$this->frupiah($rc,'j_p_1315');
	              $arrjml['j_p_1315']=$this->fjml_ttl($arrjml,'j_p_1315',$rc,'j_p_1315');

	              $tmp_dt_tb[]=$this->frupiah($rc,'jml_1315');
	              $arrjml['jml_1315']=$this->fjml_ttl($arrjml,'jml_1315',$rc,'jml_1315');

	              $tmp_dt_tb[]=$this->frupiah($rc,'j_l_1618');
	              $arrjml['j_l_1618']=$this->fjml_ttl($arrjml,'j_l_1618',$rc,'j_l_1618');

	              $tmp_dt_tb[]=$this->frupiah($rc,'j_p_1618');
	              $arrjml['j_p_1618']=$this->fjml_ttl($arrjml,'j_p_1618',$rc,'j_p_1618');

	              $tmp_dt_tb[]=$this->frupiah($rc,'jml_1618');
	              $arrjml['jml_1618']=$this->fjml_ttl($arrjml,'jml_1618',$rc,'jml_1618');

	              $tmp_dt_tb[]=$this->frupiah($rc,'jml');
	              $arrjml['jml']=$this->fjml_ttl($arrjml,'jml',$rc,'jml');
	           
	               
	            } else{
	            	$tmp_dt_tb[]=$row['kd_indv'];           

				    $tmp_dt_tb[]=$row['nama'];
				    
				    $data1 = $tb_gender->getData("Kd_gen=$row[kd_gen]");			
				    $rc = $this->build_rc($data1);

				    $tmp_dt_tb[]=$rc['Nm_gen_ind'];
	               
	                $t=explode("-",$row['tgl_lahir']);
		            $tgl_lhr=$t[2]."-".$t[1]."-".$t[0]; 
	                $tmp_dt_tb[]=$tgl_lhr;
	                		   
				    $tmp_dt_tb[]=$row['u712']==1 ? 'V':'';
				    $tmp_dt_tb[]=$row['u1315']==1 ? 'V':'';
				    $tmp_dt_tb[]=$row['u1618']==1 ? 'V':'';


	            }           

				$dt_tb[] = $tmp_dt_tb;
				$i++;
			}	
		}
		
		  $footer_tb=array();
		if(empty($idrt)){  
		  $tmp_footer=array();		       

		  foreach ($arrjml as $key=>$value) {
			$tmp_footer[]= number_format($value,0,',','.');     
		  }           

		  $footer_tb[] = $tmp_footer;          
		}
		return array('isi_tb'=>$dt_tb,'footer_tb'=>$footer_tb); 
	}

	function getdtmenu03($idkec,$iddesa,$iddusun,$idrt){ 
		
        if(empty($idrt)){
		 $kd_wl=$this->getkdwl($idkec,$iddesa,$iddusun,$idrt,'','','id_unit_detail_idk');
        }else{
         $kd_wl=$this->getkdwl($idkec,$iddesa,$iddusun,$idrt); 	
        }
		
		$tb_contr = new tb_gen('dbo_non_acptr_reas');
		$dt_contr = $tb_contr->getData('');  

		if(!empty($dt_contr)){
			$str='';
			  foreach ($dt_contr as $row) {
				$str=(!empty($str) ? $str.',':'') ."SUM(Kd_nonacptr=$row[Kd_nonacptr] and kd_fammbrtyp=1) AS j_$row[Kd_nonacptr]";
			  }			  
		}

		$arrjml = array();
        if(empty($idrt)){
		  $dt = new dt_unit_detail;              
		  $data = $dt->getdata("$kd_wl");  

	 	  $tb = new tb_gen('tbgen');
		  $tb->sql_from="vw_fam_indv";		
		  $tb->sql_select = "sum(Kd_fammbrtyp=1) AS j_kk,count(*) AS j_jiwa,$str";                           
		}else{
          $tb = new tb_gen('tbgen');
		  $tb->sql_from="vw_fam_indv";		
		  $tb->sql_select = "kd_fam,COUNT(*) AS jml_jiwa,Kd_nonacptr"; 
		  $tb->sql_groupby = 'Kd_fam';
		  $tb->sql_orderby = 'Kd_fam';              
		  $data = $tb->getData("$kd_wl pus='1' AND Kd_nonacptr!=0 AND (Kd_mutasi IS NULL)");

		  $tb_indv = new tb_gen('dbo_individu');  
		  $tb_indv->sql_select = "Nama";
		  $arrjml['jml_jiwa']=0;
          
          if(!empty($dt_contr)){                 			     
			     foreach ($dt_contr as $row) {
				   $str="j_$row[Kd_nonacptr]";			       
                   $arrjml[$str]=0;                   	   
			     }
		      }

		}

		$dt_tb=array();
		$i=1;
		
		$jml_pra=1;
		$jml_ks=1;

        if(!empty($data)){
			foreach($data as $row)
			{
				$tmp_dt_tb=array();			

				if(empty($idrt))
				{
				  $tmp_dt_tb[]=$i;
				  $tmp_dt_tb[]=$row['no_unit_detail'];    
				

				  $kd_wlq=$this->getkdwl(($idkec==0 ? $row['id_unit_detail'] : $idkec ),
				  ( (($idkec!=0) and ($iddesa == 0)) ? $row['id_unit_detail'] : $iddesa),
				  ( (($idkec!=0) and ($iddesa != 0) and ($iddusun==0)) ? $row['id_unit_detail']  : $iddusun),
				  ((($idkec!=0) and ($iddesa != 0) and ($iddusun!=0) and ($idrt==0)) ? $row['id_unit_detail']  : $idrt));          
				
				  $data1 = $tb->getData("$kd_wlq pus='1' AND Kd_nonacptr!=0 AND Kd_mutasi IS NULL");			
				  $rc = $this->build_rc($data1);
	            
	              $tmp_dt_tb[]=$this->frupiah($rc,'j_kk');
	              $arrjml['j_kk']=$this->fjml_ttl($arrjml,'j_kk',$rc,'j_kk');

	              $tmp_dt_tb[]=$this->frupiah($rc,'j_jiwa');
	              $arrjml['j_jiwa']=$this->fjml_ttl($arrjml,'j_jiwa',$rc,'j_jiwa');
	              
	              if(!empty($dt_contr)){
	                 			     
				     foreach ($dt_contr as $row) {
					   $str="j_$row[Kd_nonacptr]";
				       $tmp_dt_tb[]=$this->frupiah($rc,$str);
	                   $arrjml[$str]=$this->fjml_ttl($arrjml,$str,$rc,$str);
	                   	   
				     }
	                   
	                   
			      }
	            
	               
	            } else{
	            	$tmp_dt_tb[]=$row['Kd_fam'];
	               
	                $data1 = $tb_indv->getData("Kd_fam='$row[Kd_fam]' and Kd_fammbrtyp=1");			
				    $rc = $this->build_rc($data1);     

				    $tmp_dt_tb[]=$rc['Nama'];
				    $tmp_dt_tb[]=$row['jml_jiwa'];
				    $arrjml['jml_jiwa']=$this->fjml_ttl($arrjml,'jml_jiwa',$row,'jml_jiwa');
				    
				    if(!empty($dt_contr)){                 			     
				     foreach ($dt_contr as $row1) {
					    if($row['Kd_nonacptr']==$row1['Kd_nonacptr'])
					    {
	                      $tmp_dt_tb[]='V';
	                      $str="j_$row1[Kd_nonacptr]";
				          $arrjml[$str]=$this->fjml_ttl($arrjml[$str],'',1,'');
					    } else{
					    	$tmp_dt_tb[]='';
					    }                	   
				     }
			      }
				     
	            }           

				$dt_tb[] = $tmp_dt_tb;
				$i++;
			}	
		}
		
		$footer_tb=array();
		$tmp_footer=array();

		       

		foreach ($arrjml as $key=>$value) {
			$tmp_footer[]= $key=='prosen' ? number_format($value,2,',','.').'%' : number_format($value,0,',','.');     
		}           

		$footer_tb[] = $tmp_footer;          
		
		return array('isi_tb'=>$dt_tb,'footer_tb'=>$footer_tb); 
	}

	function getdtmenu04($idkec,$iddesa,$iddusun,$idrt){ 
		
        if(empty($idrt)){
		 $kd_wl=$this->getkdwl($idkec,$iddesa,$iddusun,$idrt,'','','id_unit_detail_idk');
        }else{
         $kd_wl=$this->getkdwl($idkec,$iddesa,$iddusun,$idrt); 	
        }
		
        $this->arrayks();

		$arrjml = array();
        if(empty($idrt)){
		  $dt = new dt_unit_detail;              
		  $data = $dt->getdata("$kd_wl");  

	 	  $tb = new tb_gen('tbgen');
		  $tb->sql_from="vw_fam_indv";		
		  $tb->sql_select = "sum(Kd_fammbrtyp=1) AS j_kk,
		                     count(*) AS j_jiwa,
		                     sum((".$this->arr_ks['pra_s'].") and Kd_fammbrtyp=1) as j_pra_s,
		                     sum((".$this->arr_ks['ks_1'].") and Kd_fammbrtyp=1) as j_ks_1,
		                     sum((".$this->arr_ks['ks_2'].") and Kd_fammbrtyp=1) as j_ks_2,
		                     sum((".$this->arr_ks['ks_3'].") and Kd_fammbrtyp=1) as j_ks_3,
		                     sum((".$this->arr_ks['ks_3_p'].") and Kd_fammbrtyp=1) as j_ks_3_p";                           
		}else{
          $tb = new tb_gen('tbgen');
		  $tb->sql_from="vw_fam_indv";		
		  $tb->sql_select = "kd_fam,COUNT(*) AS jml_jiwa,
		                     if(((".$this->arr_ks['pra_s'].") and Kd_fammbrtyp=1),1,0) as pra_s,
		                     if(((".$this->arr_ks['ks_1'].") and Kd_fammbrtyp=1),1,0) as ks_1,
		                     if(((".$this->arr_ks['ks_2'].") and Kd_fammbrtyp=1),1,0) as ks_2,
		                     if(((".$this->arr_ks['ks_3'].") and Kd_fammbrtyp=1),1,0) as ks_3,
		                     if(((".$this->arr_ks['ks_3_p'].") and Kd_fammbrtyp=1),1,0) as ks_3_p"; 
		  $tb->sql_groupby = 'Kd_fam';
		  $tb->sql_orderby = 'Kd_fam';              
		  $data = $tb->getData("$kd_wl (Kd_mutasi IS NULL)");

		  $tb_indv = new tb_gen('dbo_individu');  
		  $tb_indv->sql_select = "Nama";
		  $arrjml['jml_jiwa']=0;
          $arrjml['pra_s']=0;
          $arrjml['ks_1']=0;
          $arrjml['ks_2']=0;
          $arrjml['ks_3']=0;
          $arrjml['ks_3_p']=0;                   	   
			 
		}

		$dt_tb=array();
		$i=1;
		
		$jml_pra=1;
		$jml_ks=1;

        if(!empty($data)){
			foreach($data as $row)
			{
				$tmp_dt_tb=array();			

				if(empty($idrt))
				{
				  $tmp_dt_tb[]=$i;
				  $tmp_dt_tb[]=$row['no_unit_detail'];    
				

				  $kd_wlq=$this->getkdwl(($idkec==0 ? $row['id_unit_detail'] : $idkec ),
				  ( (($idkec!=0) and ($iddesa == 0)) ? $row['id_unit_detail'] : $iddesa),
				  ( (($idkec!=0) and ($iddesa != 0) and ($iddusun==0)) ? $row['id_unit_detail']  : $iddusun),
				  ((($idkec!=0) and ($iddesa != 0) and ($iddusun!=0) and ($idrt==0)) ? $row['id_unit_detail']  : $idrt));          
				
				  $data1 = $tb->getData("$kd_wlq Kd_mutasi IS NULL");			
				  $rc = $this->build_rc($data1);
	            
	              $tmp_dt_tb[]=$this->frupiah($rc,'j_kk');
	              $arrjml['j_kk']=$this->fjml_ttl($arrjml,'j_kk',$rc,'j_kk');

	              $tmp_dt_tb[]=$this->frupiah($rc,'j_jiwa');
	              $arrjml['j_jiwa']=$this->fjml_ttl($arrjml,'j_jiwa',$rc,'j_jiwa');
	              
	              $tmp_dt_tb[]=$this->frupiah($rc,'j_pra_s');
	              $arrjml['j_pra_s']=$this->fjml_ttl($arrjml,'j_pra_s',$rc,'j_pra_s');
	                       	   
				  $tmp_dt_tb[]=$this->frupiah($rc,'j_ks_1');
	              $arrjml['j_ks_1']=$this->fjml_ttl($arrjml,'j_ks_1',$rc,'j_ks_1');
	              
	              $tmp_dt_tb[]=$this->frupiah($rc,'j_ks_2');
	              $arrjml['j_ks_2']=$this->fjml_ttl($arrjml,'j_ks_2',$rc,'j_ks_2');
	              
	              $tmp_dt_tb[]=$this->frupiah($rc,'j_ks_3');
	              $arrjml['j_ks_3']=$this->fjml_ttl($arrjml,'j_ks_3',$rc,'j_ks_3');
	              
	              $tmp_dt_tb[]=$this->frupiah($rc,'j_ks_3_p');
	              $arrjml['j_ks_3_p']=$this->fjml_ttl($arrjml,'j_ks_3_p',$rc,'j_ks_3_p');
	              
	               
	            } else{
	            	$tmp_dt_tb[]=$row['Kd_fam'];
	               
	                $data1 = $tb_indv->getData("Kd_fam='$row[Kd_fam]' and Kd_fammbrtyp=1");			
				    $rc = $this->build_rc($data1);     

				    $tmp_dt_tb[]=$rc['Nama'];
				    $tmp_dt_tb[]=$row['jml_jiwa'];
				    $arrjml['jml_jiwa']=$this->fjml_ttl($arrjml,'jml_jiwa',$row,'jml_jiwa');
				 		    
					    if($row['pra_s']==1)
					    {
	                      $tmp_dt_tb[]='V';
	                      $arrjml['pra_s']=$this->fjml_ttl($arrjml['pra_s'],'',1,'');
					    } else{
					    	$tmp_dt_tb[]='';
					    }

					    if($row['ks_1']==1)
					    {
	                      $tmp_dt_tb[]='V';
	                      $arrjml['ks_1']=$this->fjml_ttl($arrjml['ks_1'],'',1,'');
					    } else{
					    	$tmp_dt_tb[]='';
					    }

					    if($row['ks_2']==1)
					    {
	                      $tmp_dt_tb[]='V';
	                      $arrjml['ks_2']=$this->fjml_ttl($arrjml['ks_2'],'',1,'');
					    } else{
					    	$tmp_dt_tb[]='';
					    }

					    if($row['ks_3']==1)
					    {
	                      $tmp_dt_tb[]='V';
	                      $arrjml['ks_3']=$this->fjml_ttl($arrjml['ks_3'],'',1,'');
					    } else{
					    	$tmp_dt_tb[]='';
					    }

					    if($row['ks_3_p']==1)
					    {
	                      $tmp_dt_tb[]='V';
	                      $arrjml['ks_3_p']=$this->fjml_ttl($arrjml['ks_3_p'],'',1,'');
					    } else{
					    	$tmp_dt_tb[]='';
					    }                	   
				    
				     
	            }           

				$dt_tb[] = $tmp_dt_tb;
				$i++;
			}	
		}
		
		$footer_tb=array();
		$tmp_footer=array();

		       

		foreach ($arrjml as $key=>$value) {
			$tmp_footer[]= $key=='prosen' ? number_format($value,2,',','.').'%' : number_format($value,0,',','.');     
		}           

		$footer_tb[] = $tmp_footer;          
		
		return array('isi_tb'=>$dt_tb,'footer_tb'=>$footer_tb); 
	}  

}

?>	