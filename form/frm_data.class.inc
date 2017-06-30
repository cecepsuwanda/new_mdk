<?php require_once('shared.php');
     
class frm_data
{
   
   function __construct() {
	
   }
   
   
   function form_atas($data,$jdl)
   {
	    $head_tb=new arraymuldim;		
		$isi_tb=new arraymuldim;
		$tmp = new arraymuldim;
		
		$tmp->add('ALAMAT KEPALA KELUARGA')->add('KOMPLEK')->add('PROVINSI')->add('KABUPATEN/KOTA')->add('KECAMATAN')
		    ->add('DESA/KELURAHAN')->add('DUSUN/RW')->add('RT')->add('KKI');
		$arr_tmp=$tmp->getarray();	
		
		$html_txt = "<center><bold>$jdl</bold></center><br><br>";
		
		$html_txt.= '1. ALAMAT KELUARGA<br><br>';
		
		$jml=count($arr_tmp);
		
		for($i=0;$i<$jml;$i++){
		     $isi_tb->lsub(2)->add($arr_tmp[$i])->sub()->prevlevel(2)->sub()->add(' : ')->sub()->prevlevel(2)->sub()->add($data[$i])->sub()->prevlevel(3);          
		}
		
		$head_tb->add('tbalamat','id')->add('300px','width');

		$tb_alamat = new mytable($head_tb->getarray(),array(),$isi_tb->getarray(),'');		
		$html_txt .=$tb_alamat->display('').'<br>';
		
		$head_tb->emptyarray();
		$isi_tb->emptyarray();
		
		return $html_txt;
		
   }
   
   function form_angkk($data,$newrow='')
   {
	    $head_tb=new arraymuldim;	
        $jdl_tb=new arraymuldim;		
		$isi_tb=new arraymuldim;
		
	   
	    $jdl_tb->lsub(2)->add('NO KODE ANGGOTA KELUARGA (KAK)')->sub()->prevlevel(2)
		       ->sub()->add('NAMA')->sub()->prevlevel(2)
		       ->sub()->add('HUBUNGAN DENGAN KK')->sub()->prevlevel(2)
		       ->sub()->add('JENIS KELAMIN')->sub()->prevlevel(2)
		       ->sub()->add('TEMPAT LAHIR')->sub()->prevlevel(2)
		       ->sub()->add('TANGGAL LAHIR (TGL-BLN-THN)')->sub()->add('center','align')->prevlevel(2)
		       ->sub()->add('PEKERJAAN')->sub()->prevlevel(2)
		       ->sub()->add('PENDIDIKAN TERAKHIR')->sub()->prevlevel(2)
		       ->sub()->add('STATUS PERKAWINAN')->sub()->prevlevel(2)
		       ->sub()->add('MUTASI')->sub()->prevlevel(2)
		       ->sub()->add('KET')->sub()->prevlevel(3);

		$head_tb->add('tbindv','id')->add('100%','width')->add('2','border')->add('8','cellpadding')->add('0','cellspacing')->add('border-collapse: collapse','style');
				
		
		if(!empty($data)){			
			foreach($data as $row){			    
				$isi_tb->sub();
          	  	foreach($row as $field)	  
			   	{
				  $isi_tb->sub()->add($field[0])->sub()->add('center','align')->prevlevel(2);
				} 
			    $isi_tb->prevlevel(3);
			}  
		}
				
		$tb_indv = new mytable($head_tb->getarray(),$jdl_tb->getarray(),$isi_tb->getarray(),'');    
		
		$html_txt= '2. IDENTITAS KELUARGA<br><br>';
		$html_txt .=$newrow.$tb_indv->display('').'<br>';
		
	   
	   
	   return $html_txt;
   }
   
   function form_statkk($data)
   {
	    $head_tb=new arraymuldim;	
        $tmp = new arraymuldim;		
		$isi_tb=new arraymuldim;
		
		$tmp->add('BANTUAN MODAL')
		    ->add('PASANGAN USIA SUBUR')
		    ->add('PESERTA KB')			          
		    ->add('TEMPAT PELAYANAN KB')
			->add('JENIS ALAT KB')
			->add('IMPLAN AKAN DI CABUT TAHUN DEPAN')
			->add('KAPAN MENJADI PESERTA KB (METODE KONTRASEPI YANG TERAKHIR DIPAKAI)')
			->add('ALASAN TIDAK KB');		
		$arr_tmp=$tmp->getarray();
		
		$jml=count($arr_tmp);
		
		for($i=0;$i<$jml;$i++){
		  if($i<2){	
			$isi_tb->lsub(2)->add($arr_tmp[$i])->sub()->prevlevel(2)->sub()->add(' : ')->sub()->prevlevel(2)->sub()->add($data[$i][0])->sub()->prevlevel(3);
		  }else{  
		    $isi_tb->sub()->sub('data')->sub()->add($arr_tmp[$i])->sub()->prevlevel(2)->sub()->add(' : ')->sub()->prevlevel(2)->sub()->add($data[$i][0])->sub()->prevlevel(3)
			       ->sub('attr')->add($data[$i][1],'id')->add($data[$i][2],'style')->prevlevel(3); 
		  }    
		}		
		
	    $html_txt= '3. STATUS KELUARGA DAN KB<br><br>';
		
	    $head_tb->add('tbstat','id')->add('500px','width');
		$tb_stat = new mytable($head_tb->getarray(),array(),$isi_tb->getarray(),'');		
		$html_txt .=$tb_stat->display('').'<br>';
		
		return $html_txt;
   }

   function form_indks($kd,$data2,$stat=1)
   {
	    $head_tb=new arraymuldim;	
        $jdl_tb=new arraymuldim;		
		$isi_tb=new arraymuldim;
		
		
		$head_tb->add('tbindikator','id')->add('100%','width')->add('2','border')->add('8','cellpadding')->add('0','cellspacing')->add('border-collapse: collapse','style');
		
		$jdl_tb->lsub(2)->add('NO')->sub()->add('2','rowspan')->prevlevel(2)
		       ->sub()->add('INDIKATOR')->sub()->add('2','rowspan')->prevlevel(2)
		       ->sub()->add('YA')->sub()->add('2','rowspan')->prevlevel(2)
		       ->sub()->add('TIDAK')->sub()->add('2','colspan')->prevlevel(2)
		       ->sub()->add('TIDAK BERLAKU')->sub()->add('2','rowspan')->prevlevel(3)
		       ->lsub(2)->add('ALASAN EKONOMI')->sub()->prevlevel(2)
		       ->sub()->add('NON ALASAN EKONOMI')->sub()->prevlevel(3);
		
		$dt_ind_ks = new dt_indikator_ks;
		$data = $dt_ind_ks->getdata('id_ind_ks>5 and id_ind_ks<=36');
		
		$i=1;
		$isitb = array();
		if(!empty($data))
		{
			
			foreach ($data as $row) {
			
				if($row['id_ind_ks']!=9){  
										
					$isi_tb->lsub(2)->add($i++)->sub()->prevlevel(2)
					->sub()->add($row['nm_ind_ks'])->sub()->prevlevel(2)
					->sub()->add($data2[$row['id_ind_ks']][0])->sub()->add('center','align')->prevlevel(2)
					->sub()->add($data2[$row['id_ind_ks']][1])->sub()->add('center','align')->prevlevel(2)
					->sub()->add($data2[$row['id_ind_ks']][2])->sub()->add('center','align')->prevlevel(2)
					->sub()->add($data2[$row['id_ind_ks']][3])->sub()->add('center','align')->prevlevel(3);
					
				}else{
					
					$isi_tb->lsub(2)->add($i++)->sub()->add(4,'rowspan')->prevlevel(2)
					       ->sub()->add($row['nm_ind_ks'])->sub()->prevlevel(2)
					       ->sub()->add('')->sub()->add(4,'colspan')->prevlevel(3);
					
					$data1 = $dt_ind_ks->getdata('id_ind_ks>=62 and id_ind_ks<=64'); 
					if(!empty($data1))
					{
						foreach ($data1 as $row1) {
							
							$isi_tb->lsub(2)->add($row1['nm_ind_ks'])->sub()->prevlevel(2)
							->sub()->add($data2[$row1['id_ind_ks']][0])->sub()->add('center','align')->prevlevel(2)
							->sub()->add($data2[$row1['id_ind_ks']][1])->sub()->add('center','align')->prevlevel(2)
							->sub()->add($data2[$row1['id_ind_ks']][2])->sub()->add('center','align')->prevlevel(2)
							->sub()->add($data2[$row1['id_ind_ks']][3])->sub()->add('center','align')->prevlevel(3);						
							
						} 
					}

				}
				
			}
		}		
		
		$tb_indkks = new mytable($head_tb->getarray(),$jdl_tb->getarray(),$isi_tb->getarray(),'');

		$html_txt= '4. INDIKATOR DAN STATUS TAHAPAN KELUARGA<br><br>';
		
		if($stat==1){
		  $tb_prosplvl = new tb_gen('dbo_prosp_lvl');
		  $dt = $tb_prosplvl->getData("Kd_prosplvl=".$kd);
		  $html_txt.="<center>STATUS TAHAPAN KELUARGA : ".$dt[0]['Nm_prosplvl_ind']."</center><br>";
        }
		
		$html_txt.=$tb_indkks->display();
		
		return $html_txt;
   }   
   
}

?>  