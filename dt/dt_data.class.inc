<?php require_once('shared.php');

class dt_data
{

	function __construct() {
      
		$tb = new tb_gen('tbgen');     
		$isviewexist = $tb->isviewexist('vw_fam_indv');
		if(!$isviewexist)
		{
			$tb->createview('vw_fam_indv',"SELECT fam.*,kd_indv,kd_fammbrtyp,nama,kd_gen,tgl_lahir,tpt_lahir,kd_edu,kd_martl,kd_emp,kd_mutasi,keterangan,posyandu,kd_unik_indv FROM dbo_family fam INNER JOIN dbo_individu idv ON fam.Kd_fam=idv.Kd_fam");
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

	function getdtedit($idkec,$iddesa,$iddusun,$idrt,$pageno,$rows_per_page,$where,$order)
	{
        $col = array(0=>'Kd_fam',1=>'Kd_fam',3=>'Kd_fam',4=>'nama',5=>'Kd_subdist',6=>'Kd_vill',7=>'Kd_subvill',8=>'Kd_neigh');
		
		$kd_wl=$this->getkdwl($idkec,$iddesa,$iddusun,$idrt);
        
        $tb = new tb_gen('tbgen');
        $tb->tablename='vw_fam_indv'; 
        $tb->sql_select='Kd_fam,nama,Kd_subdist,Kd_vill,Kd_subvill,Kd_neigh';
        $tb->sql_orderby='Kd_fam';
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
		
		if(!empty($where)){ 
		  $str = " AND ((nama LIKE '%$where%') or (Kd_fam LIKE '%$where%') or (Kd_subdist like '%$where%') or (Kd_vill like '%$where%') or (Kd_subvill like '%$where%')or (Kd_neigh like '%$where%'))";
          $data = $tb->getData("$kd_wl Kd_fammbrtyp=1 and Kd_mutasi IS NULL $str");
          $jmldisplaydata = $tb->numrows;		  
       }
        $dt_unit = new dt_unit_detail;
		
            $tmp_data=array();
			if(!empty($data))
			{
			  foreach ($data as $row) {
				$tmp_row = array();
				$tmp_row[]="<a href='javascript:void(0)' onclick='edt_edit_data($row[Kd_fam])'>Edit</a>";
				$tmp_row[]="<input type='checkbox' id='kdfam".$row['Kd_fam']."' name='kdfam[]' value='$row[Kd_fam]' onclick='kdfam_check()' > <a href='javascript:void(0)' onclick='edit_hapus_data($row[Kd_subdist],$row[Kd_vill],$row[Kd_subvill],$row[Kd_neigh],$row[Kd_fam])'>hapus</a>";
				$tmp_row[]="<a href='javascript:void(0)' onclick='edt_view_data($row[Kd_fam])'>".$row['Kd_fam']."</a>";
				$tmp_row[]= $row['nama'];	       
		      
						   if(empty($idkec))
							{								
							 $tmp_row[]=$dt_unit->getnm("id_unit=11 AND id_unit_detail='".$row['Kd_subdist']."'");			
							}

							if(empty($iddesa)){								
							 $tmp_row[]=$dt_unit->getnm("id_unit=12 AND id_unit_detail='".$row['Kd_vill']."'");
							}

							if(empty($iddusun))
							{								
							 $tmp_row[]=$dt_unit->getnm("id_unit=13 AND id_unit_detail='".$row['Kd_subvill']."'");
							}

							if(empty($idrt))
							{								
							 $tmp_row[]=$dt_unit->getnm("id_unit=14 AND id_unit_detail='".$row['Kd_neigh']."'");
							}
				$tmp_data[]=$tmp_row;
			  }
			}

		return  array('totaldata'=>$jmltotaldata,'displaydata'=>$jmldisplaydata,'data'=>$tmp_data);		
	}
}

?>	