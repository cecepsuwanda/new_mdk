<?php require_once('shared.php');

class vw_data
{

	function __construct() {
		
	}

	function menu_filter(){     
		$html_txt = "<center>No. Kode Keluarga Indonesia (KKI) <input type='text' id='kki_cari' name='kki_cari' size='16' maxlength='16' onkeypress='return isNumberKey(event)' ><input type='submit' value='Cari' id='cari_kki' onclick='cari_kki()'></center><br><br>";
		$html_txt .= "<div id='data'>";
		$html_txt .= "</div>";
		return $html_txt; 
	}

	function menu_filter1(){
		$frmfilter = new frm_filter;
		$html_txt = $frmfilter->cmb_filter()."<br><br>";
		$html_txt .= "<div id='data'>";
		$html_txt .= "</div>";
		$html_txt .= "<div id='dialog'>";
		$html_txt .= "</div>";

		return $html_txt; 
	}

	function kki_exist($kki){
		$dt = new dt_family;
		return $dt->kki_exist($kki);
	}

	function kak_exist($kak){
		$dt = new dt_individu;
		$isempty = true;
		$jml=count($kak);
		$max = $jml>0 ? max(array_keys($kak)) : 0;    
		$jml = ($jml<$max) ? $max : $jml;    
		$i=1;

		while (($i <= $jml) and ($isempty)){      
			if(isset($kak[$i])){
				$isempty = ($dt->kak_exist($kak[$i]['kak'])==0);  
			} 
			if($isempty) $i++; 

		}      

		return $isempty ? 0 : $i;
	}

	function get_kki($iddesa){
		$dtfam = new dt_family;
		$tmp_kki = $dtfam->getkki($iddesa);
		return $tmp_kki;
	}

	function get_kak($iddesa)
	{
		
		$dtindv = new dt_individu;
		$tmp_kak = $dtindv->getkak($iddesa);
		return $tmp_kak;
	}
	
	function view_pos($param)
	{
		$arr_pos = array(null=>'Tidak Ikut Posyandu','1'=>'Ikut Posyandu');
		$pos = isset($arr_pos[$param]) ? $arr_pos[$param] : '';
		return $pos;
	}
	
	function update_pos($param)
	{
		$pos = "";
		$i=$param['i'];
		$isdisable=$param['isdisable'];
		$Posyandu=$param['Posyandu'];  
				    
		   $pos = "Ikut Program Posyandu :
	               <br><input type='radio' id='yd$i' name='indv[$i][yd]' value='1' ". (($Posyandu=='1') ? 'checked':'')." $isdisable >Ya 
	                   <input type='radio' id='yd$i' name='indv[$i][yd]' value='0' ". (($Posyandu==null) ? 'checked':'')." $isdisable >Tidak";
	    	
		return $pos;
	}
	
	
	
	function cek_pos($fpos,$param,$tgl_lhr)
	{
		$t=explode('-',$tgl_lhr);
		$t1=date('j');
	    $b=date('n');
		$y=date('Y');
		
		$pos = '';

		if(($t[0]>($y-5)) or (($t[0]==($y-5)) and ((intval($t[1])>$b) or ((intval($t[1])==$b) and (intval($t[2])>$t1)))))
		{		  
		  $pos = $this->$fpos($param);
		}
		
		return $pos;
	}
	
	function tambah_form_atas($data)
	{
		$mycmb=new mycmb;		
		$unit = new dt_unit_detail;
		$tmp=new arraymuldim;
		
		$tmp->add("<input type='text' id='almt' name='fam[almt]' size='70' value=''>")
		       ->add("<input type='text' id='komp' name='fam[komp]' size='40' value=''>")
		       ->add(' JAWA BARAT')
		       ->add(' KABUPATEN BANDUNG BARAT')
		       ->add("<select id='kec' name='fam[kec]' >".$mycmb->cmb_kec($unit->getkec(),'Pilih Kecamatan')."</select>")
		       ->add("<select id='desa' name ='fam[desa]'>".$mycmb->cmb_desa(array(),'Pilih Desa/Kelurahan')."</select>")
		       ->add("<select id='dusun' name='fam[dusun]' >".$mycmb->cmb_dusun(array(),'Pilih Dusun/RW')."</select>")
		       ->add("<select id='rt' name='fam[rt]' >".$mycmb->cmb_rt(array(),'Pilih RT')."</select>")
		       ->add("<input type='text' id='pref' name='fam[pref]' size='10' maxlength='10' value='' disabled >  <input type='text' id='kki' name='fam[kki]' size='7' maxlength='7' onkeypress='return isNumberKey(event)' value='' >");           
			
		return $tmp;
	}
	
	function update_form_atas($data)
	{
		$mycmb=new mycmb;		
		$unit = new dt_unit_detail;
		$tmp=new arraymuldim;
		
		$tmp->add("<input type='text' id='almt' name='fam[almt]' size='70' value='".$data[0]['alamat']."'>")
		       ->add("<input type='text' id='komp' name='fam[komp]' size='40' value='".$data[0]['komplek']."'>")
		       ->add(' JAWA BARAT')
		       ->add(' KABUPATEN BANDUNG BARAT')
		       ->add("<select id='kec' name='fam[kec]' >".$mycmb->cmb_kec($unit->getkec(),'Pilih Kecamatan',$data[0]['Kd_subdist'])."</select>")
		       ->add("<select id='desa' name ='fam[desa]'>".$mycmb->cmb_desa($unit->getdesa($data[0]['Kd_subdist']),'Pilih Desa/Kelurahan',$data[0]['Kd_vill'])."</select>")
		       ->add("<select id='dusun' name='fam[dusun]' >".$mycmb->cmb_dusun($unit->getdusun($data[0]['Kd_vill']),'Pilih Dusun/RW',$data[0]['Kd_subvill'])."</select>")
		       ->add("<select id='rt' name='fam[rt]' >".$mycmb->cmb_rt($unit->getrt($data[0]['Kd_subvill']),'Pilih RT',$data[0]['Kd_neigh'])."</select>")
		       ->add("<input type='hidden' id='preflama' name='fam[preflama]' value='".$data[0]['Kd_vill']."'><input type='text' id='pref' name='fam[pref]' size='10' maxlength='10' value='".$data[0]['Kd_vill']."' disabled >  <input type='hidden' id='kkilama' name='fam[kkilama]' value='".$data[0]['Kd_unik_fam']."'><input type='text' id='kki' name='fam[kki]' size='7' maxlength='7' onkeypress='return isNumberKey(event)' value='".$data[0]['Kd_unik_fam']."' >");           
			
		return $tmp;
	}
	
	function view_form_atas($data)
	{
				
		$unit = new dt_unit_detail;
		$tmp=new arraymuldim;		
		
		$tmp->add($data[0]['alamat'])
		       ->add($data[0]['komplek'])
		       ->add(' JAWA BARAT')
		       ->add(' KABUPATEN BANDUNG BARAT')
		       ->add($unit->getnm("id_unit=11 AND id_unit_detail='".$data[0]['Kd_subdist']."'"))
		       ->add($unit->getnm("id_unit=12 AND id_unit_detail='".$data[0]['Kd_vill']."'"))
		       ->add($unit->getnm("id_unit=13 AND id_unit_detail='".$data[0]['Kd_subvill']."'"))
		       ->add($unit->getnm("id_unit=14 AND id_unit_detail='".$data[0]['Kd_neigh']."'"))
		       ->add($data[0]['Kd_fam']);
					
		return $tmp;
	}
	
	function tambah_form_angkk($data_indv)
	{
		$tb_fammbrtyp = new tb_gen('dbo_fam_mbr_typ');
		$tb_gender = new tb_gen('dbo_gender');
		$tb_martlstat = new tb_gen('dbo_martl_stat');
		$tb_mutasi = new tb_gen('dbo_mutasi');
		
		$dt_empmntstat = new dt_empmnt_stat;
		$dt_edulvl = new dt_edu_lvl;
		
		$mycmb=new mycmb;
		$tmp=new arraymuldim;
		
		for($i=1;$i<=5;$i++)
		{
				
				$hub_dis= $i==1 ? 'disabled' : '';
			    $selfammbrtyp= ($i<=2) ? $i : 3;
			    $seljk = ($selfammbrtyp==2) ? 2 : 1;
			    $selstat = in_array($selfammbrtyp, array(1,2)) ? 2 : 1;
			    $stat_dis = ($selfammbrtyp==2) ? 'disabled' : '';

				

			   $tmp->lsub(2)->add("<input type='text' id='kak$i' name='indv[$i][kak]' size='7' maxlength='7' value='' onkeypress='return isNumberKey(event)' >")->prevlevel(1)
				       ->sub()->add("<input type='text' id='nm$i' name='indv[$i][nm]' value='' >")->prevlevel(1)
				       ->sub()->add("<select id='hub$i' name='indv[$i][hub]' onChange='bg_wrn_slct($i)' $hub_dis >".$mycmb->cmb_hbkk($tb_fammbrtyp->getData(''),$selfammbrtyp)."</select>")->prevlevel(1)
				       ->sub()->add("<select id='jk$i' name='indv[$i][jk]'  >".$mycmb->cmb_jk($tb_gender->getData(''),$seljk)."</select>")->prevlevel(1)
				       ->sub()->add("<input type='text' id='tpt_lhr$i' name='indv[$i][tpt_lhr]' value='' size='20' >")->prevlevel(1)
				       ->sub()->add("<input type='text' id='tlhr$i' name='indv[$i][tlhr]' size='10' maxlength = '10' value='' onkeypress='return isNumberKey1(event)' onKeyUp='tlhr_change(event,this,$i)' ><div id='div_pos_yd$i'></div>")->prevlevel(1)
				       ->sub()->add("<select id='pkr$i' name='indv[$i][pkr]'  >".$mycmb->cmb_kerja($dt_empmntstat->getdata(''))."</select>")->prevlevel(1)
				       ->sub()->add("<select id='pdk$i' name='indv[$i][pdk]'  >".$mycmb->cmb_edu($dt_edulvl->getdata(''))."</select>")->prevlevel(1)
				       ->sub()->add("<select id='sts_mtr$i' name='indv[$i][sts_mtr]' $stat_dis >".$mycmb->cmb_stat($tb_martlstat->getData(''),$selstat)."</select>")->prevlevel(1)
				       ->sub()->add("<select id='mts$i' name='indv[$i][mts]' onChange='mts_change($i)' >".$mycmb->cmb_mutasi($tb_mutasi->getData(''))."</select>")->prevlevel(1)
				       ->sub()->add("<input type='text' id='ket$i' name='indv[$i][ket]' value=''  >")->prevlevel(2);
						
		}
		
		return $tmp;
	}
	
	function update_form_angkk($data_indv)
	{
		$tb_fammbrtyp = new tb_gen('dbo_fam_mbr_typ');
		$tb_gender = new tb_gen('dbo_gender');
		$tb_martlstat = new tb_gen('dbo_martl_stat');
		$tb_mutasi = new tb_gen('dbo_mutasi');
		
		$dt_empmntstat = new dt_empmnt_stat;
		$dt_edulvl = new dt_edu_lvl;
		
		$mycmb=new mycmb;
		$tmp=new arraymuldim;
		
		if(!empty($data_indv)){        
			$i=1;
			foreach ($data_indv as $row) {
				
				    $isdisable =  ($row['Kd_mutasi'] != Null) ? 'disabled' : '';
					$isdisable1=  ($row['Kd_mutasi'] != Null) ? 'disabled' : ''; 
					$isdisable1=  ($row['Kd_fammbrtyp']==2)   ? 'disabled' : '';

				$tgl_kb=$row['Tgl_lahir'];
				$t=explode('-',$tgl_kb);         
				$tgl_kb=$t[2]."-".$t[1]."-".$t[0];

				$pos=$this->cek_pos('update_pos',array('Posyandu'=>$row['Posyandu'],'i'=>$i,'isdisable'=>$isdisable),$row['Tgl_lahir']);

			   $tmp->lsub(2)->add("<input type='hidden' id='kaklama$i' name='indv[$i][kaklama]' value='$row[Kd_unik_indv]'><input type='text' id='kak$i' name='indv[$i][kak]' size='7' maxlength='7' value='$row[Kd_unik_indv]' onkeypress='return isNumberKey(event)' $isdisable >")->prevlevel(1)
				       ->sub()->add("<input type='text' id='nm$i' name='indv[$i][nm]' value='$row[Nama]' $isdisable >")->prevlevel(1)
				       ->sub()->add("<select id='hub$i' name='indv[$i][hub]' onChange='bg_wrn_slct($i)' $isdisable >".$mycmb->cmb_hbkk($tb_fammbrtyp->getData(''),$row['Kd_fammbrtyp'])."</select>")->prevlevel(1)
				       ->sub()->add("<select id='jk$i' name='indv[$i][jk]' $isdisable >".$mycmb->cmb_jk($tb_gender->getData(''),$row['Kd_gen'])."</select>")->prevlevel(1)
				       ->sub()->add("<input type='text' id='tpt_lhr$i' name='indv[$i][tpt_lhr]' value='$row[Tpt_lahir]' size='20' $isdisable >")->prevlevel(1)
				       ->sub()->add("<input type='text' id='tlhr$i' name='indv[$i][tlhr]' size='10' maxlength = '10' value='$tgl_kb' onkeypress='return isNumberKey1(event)' onKeyUp='tlhr_change(event,this,$i)' $isdisable ><div id='div_pos_yd$i'>$pos</div>")->prevlevel(1)
				       ->sub()->add("<select id='pkr$i' name='indv[$i][pkr]' $isdisable >".$mycmb->cmb_kerja($dt_empmntstat->getdata(''),$row['Kd_emp'])."</select>")->prevlevel(1)
				       ->sub()->add("<select id='pdk$i' name='indv[$i][pdk]' $isdisable >".$mycmb->cmb_edu($dt_edulvl->getdata(''),$row['Kd_edu'])."</select>")->prevlevel(1)
				       ->sub()->add("<select id='sts_mtr$i' name='indv[$i][sts_mtr]' $isdisable1 >".$mycmb->cmb_stat($tb_martlstat->getData(''),$row['Kd_martl'])."</select>")->prevlevel(1)
				       ->sub()->add("<select id='mts$i' name='indv[$i][mts]' onChange='mts_change($i)' >".$mycmb->cmb_mutasi($tb_mutasi->getData(''),$row['Kd_mutasi'])."</select>")->prevlevel(1)
				       ->sub()->add("<input type='text' id='ket$i' name='indv[$i][ket]' value='$row[Keterangan]' $isdisable >")->prevlevel(2);
				
				$i++;
			}  
		}
		
		return $tmp;
	}
	
	function view_form_angkk($data_indv)
	{
		$tb_fammbrtyp = new tb_gen('dbo_fam_mbr_typ');
		$tb_gender = new tb_gen('dbo_gender');
		$tb_martlstat = new tb_gen('dbo_martl_stat');
		$tb_mutasi = new tb_gen('dbo_mutasi');
		
		$dt_empmntstat = new dt_empmnt_stat;
		$dt_edulvl = new dt_edu_lvl;
				
		$tmp=new arraymuldim;
		
		if(!empty($data_indv)){        
			
			foreach ($data_indv as $row) {
				
				$dt=$tb_fammbrtyp->getData("Kd_fammbrtyp='$row[Kd_fammbrtyp]'"); 
				$hub = $dt[0]['Nm_fammbrtyp_ind'];

				$dt=$tb_gender->getData("Kd_gen='$row[Kd_gen]'");
				$jk = $dt[0]['Nm_gen_ind'];

				$tgl_kb=$row['Tgl_lahir'];
				$t=explode('-',$tgl_kb);         
				$tgl_kb=$t[2]."/".$t[1]."/".$t[0];

				$pos=$this->cek_pos('view_pos',$row['Posyandu'],$row['Tgl_lahir']);

				$dt=$tb_martlstat->getData("Kd_martl='$row[Kd_martl]'");
				$sts_mtr = $dt[0]['Nm_martl_ind'];  

				$dt=$tb_mutasi->getData("Kd_mutasi='$row[Kd_mutasi]'");
				$mts = isset($dt[0]['Nm_mutasi']) ? $dt[0]['Nm_mutasi'] : '';

				$ket = isset($row['Keterangan']) ? $row['Keterangan'] :'';

				$tmp->lsub(2)->add($row['Kd_indv'])->prevlevel(1)
				       ->sub()->add($row['Nama'])->prevlevel(1)
				       ->sub()->add($hub)->prevlevel(1)
				       ->sub()->add($jk)->prevlevel(1)
				       ->sub()->add($row['Tpt_lahir'])->prevlevel(1)
				       ->sub()->add($tgl_kb.'<br>'.$pos)->prevlevel(1)
				       ->sub()->add($dt_empmntstat->getnm1($row['Kd_emp']))->prevlevel(1)
				       ->sub()->add($dt_edulvl->getnm1($row['Kd_edu']))->prevlevel(1)
				       ->sub()->add($sts_mtr)->prevlevel(1)
				       ->sub()->add($mts)->prevlevel(1)
				       ->sub()->add($ket)->prevlevel(2);
			
			}  
		}
		
		return $tmp;
	}
	
	function tambah_form_statkk($data)
	{
		$dt_contrtyp = new dt_contr_typ;
		$dt_nonacptr = new dt_non_acptr_reas;
		
		$mycmb=new mycmb;
		$tmp=new arraymuldim;
		
		$tmp->sub()->add("<input type='radio' id='btm' name='fam[btm]' value='1' >Ya <input type='radio' id='btm' name='fam[btm]' value='0' >Tidak")->prevlevel()
		    ->sub()->add("<input type='radio' id='pus' name='fam[pus]' value='1' onclick='proc_pus(this)' >Ya <input type='radio' id='pus' name='fam[pus]' value='0' onclick='proc_pus(this)' >Tidak")->prevlevel()
		    ->sub()->add("<input type='radio' id='kb' name='fam[kb]' value='1' onclick='proc_kb(this)' >Ya <input type='radio' id='kb' name='fam[kb]' value='0' onclick='proc_kb(this)' >Tidak")
			       ->add('row_kb')->add('display:none;')->prevlevel() 
			->sub()->add("<input type='radio' id='src' name='fam[src]' value='1' >Pemerintah <input type='radio' id='src' name='fam[src]' value='2' >Swasta")
			       ->add('row_src')->add('display:none;')->prevlevel() 
			->sub()->add("<select id='alt_kb' name='fam[alt_kb]' onChange='proc_alt_kb(this)' >".$mycmb->cmb_contyp($dt_contrtyp->getData(''))."</select>")
			       ->add('row_alt_kb')->add('display:none;')->prevlevel()      
			->sub()->add("<input type='radio' id='ipl' name='fam[ipl]' value='1' >Ya <input type='radio' id='ipl' name='fam[ipl]' value='0' >Tidak")
			       ->add('row_ipl')->add('display:none;')->prevlevel()
			->sub()->add("<input type='text' id='tkont' name='fam[tkont]' size='10' maxlength = '10' onkeypress='return isNumberKey1(event)' value='' >")
			       ->add('row_tkont')->add('display:none;')->prevlevel()
			->sub()->add("<select id='s_bkb' name = 'fam[s_bkb]'>".$mycmb->cmb_nonkb($dt_nonacptr->getData(''))."</select>") 					  
		           ->add('row_s_bkb')->add('display:none;')->prevlevel();
		
		return $tmp;
	}
	
	function update_form_statkk($data)
	{
		$dt_contrtyp = new dt_contr_typ;
		$dt_nonacptr = new dt_non_acptr_reas;
		
		$mycmb=new mycmb;
		$tmp=new arraymuldim;
		
		if(($data[0]['pus']==1) and ($data[0]['Kd_nonacptr']==Null)){
			$tgl_kb=$data[0]['tgl_kb'];
			$t=explode('-',$tgl_kb);         
			$tgl_kb=$t[2]."-".$t[1]."-".$t[0];
		}

		$tmp->sub()->add("<input type='radio' id='btm' name='fam[btm]' value='1' ".($data[0]['Bantuan_modal']==1 ? 'checked' : '')." >Ya <input type='radio' id='btm' name='fam[btm]' value='0' ".($data[0]['Bantuan_modal']==0 ? 'checked' : '')." >Tidak")->prevlevel()
		    ->sub()->add("<input type='radio' id='pus' name='fam[pus]' value='1' onclick='proc_pus(this)' ".($data[0]['pus']==1 ? 'checked' : '')." >Ya <input type='radio' id='pus' name='fam[pus]' value='0' onclick='proc_pus(this)' ".($data[0]['pus']==0 ? 'checked' : '')." >Tidak")->prevlevel()
		    ->sub()->add("<input type='radio' id='kb' name='fam[kb]' value='1' onclick='proc_kb(this)' ".(($data[0]['pus']==1 and $data[0]['Kd_nonacptr']==Null) ? 'checked' : '')." >Ya <input type='radio' id='kb' name='fam[kb]' value='0' onclick='proc_kb(this)' ".($data[0]['Kd_nonacptr']!=Null ? 'checked' : '')." >Tidak")
			       ->add('row_kb')->add(($data[0]['pus']==1 ? '':'display:none;'))->prevlevel() 
			->sub()->add("<input type='radio' id='src' name='fam[src]' value='1' ".($data[0]['Kd_consrc']==1 ? 'checked' : '')." >Pemerintah <input type='radio' id='src' name='fam[src]' value='2' ".($data[0]['Kd_consrc']==2 ? 'checked' : '')." >Swasta")
			       ->add('row_src')->add((($data[0]['pus']==1 and $data[0]['Kd_nonacptr']==Null) ? '' : 'display:none;'))->prevlevel() 
			->sub()->add("<select id='alt_kb' name='fam[alt_kb]' onChange='proc_alt_kb(this)' >".$mycmb->cmb_contyp($dt_contrtyp->getData(''),$data[0]['Kd_contyp'])."</select>")
			       ->add('row_alt_kb')->add((($data[0]['pus']==1 and $data[0]['Kd_nonacptr']==Null) ? '' : 'display:none;'))->prevlevel()      
			->sub()->add("<input type='radio' id='ipl' name='fam[ipl]' value='1' ".($data[0]['Kd_implan']==1 ? 'checked' : '')." >Ya <input type='radio' id='ipl' name='fam[ipl]' value='0' ".($data[0]['Kd_implan']==0 ? 'checked' : '')." >Tidak")
			       ->add('row_ipl')->add((($data[0]['Kd_nonacptr']==Null and $data[0]['Kd_contyp']==4) ? '':'display:none;'))->prevlevel()
			->sub()->add("<input type='text' id='tkont' name='fam[tkont]' size='10' maxlength = '10' onkeypress='return isNumberKey1(event)' value='".( (($data[0]['pus']==1) and ($data[0]['Kd_nonacptr']==Null)) ?  $tgl_kb :'')."' >")
			       ->add('row_tkont')->add((($data[0]['pus']==1 and $data[0]['Kd_nonacptr']==Null) ? '' : 'display:none;'))->prevlevel()
			->sub()->add("<select id='s_bkb' name = 'fam[s_bkb]'>".$mycmb->cmb_nonkb($dt_nonacptr->getData(''),$data[0]['Kd_nonacptr'])."</select>") 					  
		           ->add('row_s_bkb')->add(($data[0]['Kd_nonacptr']!=Null ? '' : 'display:none;'))->prevlevel();
		
		return $tmp;
	}
	
	function view_form_statkk($data)
	{
		$dt_contrtyp = new dt_contr_typ;
		$dt_nonacptr = new dt_non_acptr_reas;
		
		$tmp=new arraymuldim;
		
		if(($data[0]['pus']==1) and ($data[0]['Kd_nonacptr']==Null)){
			$tgl_kb=$data[0]['tgl_kb'];
			$t=explode('-',$tgl_kb);         
			$tgl_kb=$t[2]."-".$t[1]."-".$t[0];
		}

		$tmp->sub()->add($data[0]['Bantuan_modal']==1 ? ' Ya' : ' Tidak')->prevlevel()
		    ->sub()->add($data[0]['pus']==1 ? ' Ya' :' Tidak')->prevlevel()
		    ->sub()->add($data[0]['Kd_nonacptr']==Null ? ' Ya' : ' Tidak')
			       ->add('row_kb')->add(($data[0]['pus']==1 ? '':'display:none;'))->prevlevel() 
			->sub()->add($data[0]['Kd_consrc']==1 ? ' Pemerintah' : ' Swasta')
			       ->add('row_src')->add((($data[0]['pus']==1 and $data[0]['Kd_nonacptr']==Null) ? '' : 'display:none;'))->prevlevel() 
			->sub()->add( ( isset($data[0]['Kd_contyp']) and !empty($data[0]['Kd_contyp'])) ? $dt_contrtyp->getnm1($data[0]['Kd_contyp']):'')
			       ->add('row_alt_kb')->add((($data[0]['pus']==1 and $data[0]['Kd_nonacptr']==Null) ? '' : 'display:none;'))->prevlevel()      
			->sub()->add($data[0]['Kd_implan']==1 ? ' Ya' : ' Tidak')
			       ->add('row_ipl')->add((($data[0]['Kd_nonacptr']==Null and $data[0]['Kd_contyp']==4) ? '':'display:none;'))->prevlevel()
			->sub()->add((($data[0]['pus']==1) and ($data[0]['Kd_nonacptr']==Null)) ?  ' '.$tgl_kb :'')
			       ->add('row_tkont')->add((($data[0]['pus']==1 and $data[0]['Kd_nonacptr']==Null) ? '' : 'display:none;'))->prevlevel()
			->sub()->add(( isset($data[0]['Kd_nonacptr']) and !empty($data[0]['Kd_nonacptr'])) ? $dt_nonacptr->getnm1($data[0]['Kd_nonacptr']) : '') 					  
		           ->add('row_s_bkb')->add((($data[0]['pus']==1 and $data[0]['Kd_nonacptr']!=Null) ? '' : 'display:none;'))->prevlevel();
		
		return $tmp;
	}
	
	function tambah_form_indks($ind_ks)
	{
		$tmp=new arraymuldim;
		if(!empty($ind_ks))
		{
			
			foreach ($ind_ks as $key=>$val) {
								
					$tmp->sub($key)->add("<input type='radio' id='ind_ks_$key' name='ind_ks[$key]' value='1' >")
					           ->add("<input type='radio' id='ind_ks_$key' name='ind_ks[$key]' value='3' >")
					           ->add("<input type='radio' id='ind_ks_$key' name='ind_ks[$key]' value='2' >")
					           ->add("<input type='radio' id='ind_ks_$key' name='ind_ks[$key]' value='4' >")->prevlevel();
					
				
			}
		}
		
		return $tmp;
	}
	
	function update_form_indks($ind_ks)
	{
		$tmp=new arraymuldim;
		if(!empty($ind_ks))
		{
			
			foreach ($ind_ks as $key=>$val) {
				
				$ischecked1 = '';
				$ischecked2 = '';
				$ischecked3 = '';
				$ischecked4 = '';				
					
					switch($val)
					{
					case 1 : $ischecked1='checked'; break;
					case 2 : $ischecked2='checked'; break;
					case 3 : $ischecked3='checked'; break;
					case 4 : $ischecked4='checked'; break;
					}  
					
					$tmp->sub($key)->add("<input type='radio' id='ind_ks_$key' name='ind_ks[$key]' value='1' $ischecked1 >")
					           ->add("<input type='radio' id='ind_ks_$key' name='ind_ks[$key]' value='3' $ischecked3 >")
					           ->add("<input type='radio' id='ind_ks_$key' name='ind_ks[$key]' value='2' $ischecked2 >")
					           ->add("<input type='radio' id='ind_ks_$key' name='ind_ks[$key]' value='4' $ischecked4 >")->prevlevel();
					
				
			}
		}
		
		return $tmp;
	}
	
	function view_form_indks($ind_ks)
	{
		$tmp=new arraymuldim;
		if(!empty($ind_ks))
		{
			
			foreach ($ind_ks as $key=>$val) {
				
				$ischecked1 = '';
				$ischecked2 = '';
				$ischecked3 = '';
				$ischecked4 = '';				
					
					switch($val)
					{
					case 1 : $ischecked1='V'; break;
					case 2 : $ischecked2='V'; break;
					case 3 : $ischecked3='V'; break;
					case 4 : $ischecked4='V'; break;
					}  
					
					$tmp->sub($key)->add($ischecked1)
					           ->add($ischecked3)
					           ->add($ischecked2)
					           ->add($ischecked4)->prevlevel();
					
				
			}
		}
		
		return $tmp;
	}
	
	
	function form_atas($kki,$jdl,$fstr)
	{
		
		$frmdata = new frm_data;
        $tmp=new arraymuldim;		
		
		if($kki!=''){
		  $dt_fam = new dt_family;
		  $data = $dt_fam->getdata("Kd_fam='$kki'");
		}else{
			$data=array();
		}
		$tmp=$this->$fstr($data);
		
		$html_txt=$frmdata->form_atas($tmp->getarray(),$jdl);
		return $html_txt;
	}
	
	function form_angkk($kki,$fstr,$isnewrow=1,$islastkak=1)
	{
		
		$frmdata = new frm_data;
        $tmp=new arraymuldim;
		
		if($kki!=''){
		    $dt_fam = new dt_family;
			$data = $dt_fam->getdata("Kd_fam='$kki'");
			
			$dt_indv = new dt_individu;
			$data_indv=$dt_indv->getdata("Kd_fam='$kki'");
		}else{
			$data_indv=array();
		}
		
		$tmp=$this->$fstr($data_indv);		
								
		$tmp_str  = $isnewrow==1 ? "<a href='javascript:void(0)' onclick='tambah_baris()'>Tambah Anggota Keluarga</a>" : '';
		$tmp_str .= $islastkak==1 ? " <label id='nokakakhir'>No KAK Terakhir : ".$dt_indv->getkak($data[0]['Kd_vill'])."</label>" : '';
		$tmp_str .= empty($tmp_str) ? '' : "<br><br>";
		
		$html_txt=$frmdata->form_angkk($tmp->getarray(),$tmp_str);
		
		return $html_txt;
	}
	
	function form_statkk($kki,$fstr)
	{
		
		$frmdata = new frm_data;
        $tmp=new arraymuldim;				
		
        if($kki!=''){		
		   $dt_fam = new dt_family;
		   $data = $dt_fam->getdata("Kd_fam='$kki'");
		}else{
			$data=array();
		}
		$tmp=$this->$fstr($data);		
        $html_txt=$frmdata->form_statkk($tmp->getarray());
		
		return $html_txt;
	}
	
	function form_indks($kki,$fstr)
	{
		if($kki!=''){
		  $dt_fam = new dt_family;
		  $data = $dt_fam->getdata("Kd_fam='$kki'");
		  $prosplvl = $data[0]['Kd_prosplvl'];
		}else{
		  $prosplvl ='';	
		}
		
		$frmdata = new frm_data;
        $tmp=new arraymuldim;
		
        if($kki!=''){		
		  $dt_ind_ks=new dt_fam_ind_detail;		
		  $ind_ks = $dt_ind_ks->get_ind_ks($kki);
		}else{
			$dt_ind_ks = new dt_indikator_ks;
		    $ind_ks = $dt_ind_ks->get_ind_ks('id_ind_ks>5');
		}
		
		$tmp=$this->$fstr($ind_ks);		
		
		$html_txt=$frmdata->form_indks($prosplvl,$tmp->getarray(),$kki=='' ? 0 : 1);
		
		return $html_txt;
	}
	

	function view_data($kki)
	{
		
        $html_txt=$this->form_atas($kki,'DATA KELUARGA','view_form_atas');		
		$html_txt.=$this->form_angkk($kki,'view_form_angkk',0,0);
        $html_txt.=$this->form_statkk($kki,'view_form_statkk');		
		$html_txt.=$this->form_indks($kki,'view_form_indks');

		return $html_txt;
	}

	function from_update($kki)
	{
		$html_txt=$this->form_atas($kki,'FORMULIR PEMUTAKHIRAN DATA KELUARGA (MDK)','update_form_atas');		
		$html_txt.=$this->form_angkk($kki,'update_form_angkk');
        $html_txt.=$this->form_statkk($kki,'update_form_statkk');
		$html_txt.=$this->form_indks($kki,'update_form_indks');
		
		return $html_txt;
	}

	function from_edit($kki)
	{
		$html_txt=$this->form_atas($kki,'FORMULIR PEMUTAKHIRAN DATA KELUARGA (MDK)','update_form_atas');		
		$html_txt.=$this->form_angkk($kki,'update_form_angkk');
        $html_txt.=$this->form_statkk($kki,'update_form_statkk');
		$html_txt.=$this->form_indks($kki,'update_form_indks');
		
		return $html_txt;
	}

	function edt_view_data($kki)
	{
		$tmp="<div id='dialog-view-$kki' title='View Data'>".$this->view_data($kki)."</div>";
		return $tmp;
	}

	function edt_edit_data($kki)
	{
		$tmp="<div id='dialog-edit-$kki' title='Edit Data'>
              <form id='frmupdate' name='frmupdate' action='#' method='post' >".$this->from_edit($kki)."</form>
          </div>";
		return $tmp;
	}


	function view_form_update($kki)
	{
		$dt = new dt_family;
		if($dt->kki_exist($kki)==1){
			$tmp="<form id='frmupdate' name='frmupdate' action='#' method='post' >".$this->from_update($kki)."<br><br><center><input type='button' value='Update Data Keluarga' id='update_data' onclick='form_update()'></center></form>";
		}else{
			$tmp="<center>No. Kode Keluarga Indonesia (KKI) $kki Tidak Ada Didatabase</center>";
		}
		return $tmp;
	}

	function after_tambah_data($kki)
	{
		$tmp=$this->view_data($kki)."<br><br><center><input type='button' value='Kembali Ke Penambahan Data Keluarga' id='tambah_data' onclick='return_form_add()'></center>";
		return $tmp;
	}

	function after_update_data($kki)
	{
		$tmp=$this->view_data($kki)."<br><br><center><input type='button' value='Kembali Ke Update Data Keluarga' id='update_data' onclick='return_form_update($kki)'></center>";
		return $tmp;
	} 

	function tambah_data()
	{
		$html_txt=$this->form_atas('','FORMULIR PEMUTAKHIRAN DATA KELUARGA (MDK)','tambah_form_atas');
		$html_txt.=$this->form_angkk('','tambah_form_angkk',1,0);
		$html_txt.=$this->form_statkk('','tambah_form_statkk');
		$html_txt.=$this->form_indks('','tambah_form_indks');
		$html_txt ="<form id='frminput' name='frminput' action='#' method='post' >".$html_txt."<br><br><center><input type='button' value='Simpan Data Keluarga' id='simpan_data' onclick='form_add()'></center></form>";
		return $html_txt;
	}

	private function getsubjudul($idkec,$iddesa,$iddusun,$idrt)
	{
		$dtunit = new dt_unit_detail;         
		$subjudul='KAB/KOTA :KABUPATEN BANDUNG BARAT ';         
		$subjudul .= ($idkec>0) ? ' >> KECAMATAN : '.$dtunit->getnm("id_unit_detail='$idkec'") : '';        
		$subjudul .= ($iddesa>0) ? ' >> DESA : '.$dtunit->getnm("id_unit_detail='$iddesa'") : '';
		$subjudul .= ($iddusun>0) ? ' >> RW : '.$dtunit->getnm("id_unit_detail='$iddusun'") : '';   
		$subjudul .= ($idrt>0) ? ' >> RT : '.$dtunit->getnm("id_unit_detail='$idrt'") : '';         

		return $subjudul;  
	}   

	function tb_edt_data($idkec,$iddesa,$iddusun,$idrt)
	{
		$subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
		$html_txt = "<center><bold>DAFTAR KEPALA KELUARGA</bold><br>$subjudul</center>";		
		
		$jdl_tb = array(array(array('OPTION',array('colspan'=>2)),
		                      array('NO. KKI',array('rowspan'=>2)),
							  array('KEPALA KELUARGA',array('rowspan'=>2))
		                     ),
		                array(array('Edit',array()),
						      array('Print | Hapus <br> cek semua uncek semua',array())
		                     )
		               );			   
			      
		if(empty($idkec))
		{
			$jdl_tb[0][]=array('KECAMATAN',array('rowspan'=>2));						
		}

		if(empty($iddesa)){
			$jdl_tb[0][]=array('DESA/KELURAHAN',array('rowspan'=>2));			
		}

		if(empty($iddusun))
		{
			$jdl_tb[0][]=array('DUSUN/RW',array('rowspan'=>2));
		}

		if(empty($idrt))
		{
			$jdl_tb[0][]=array('RT',array('rowspan'=>2));
		}

        $dt_tb=array();
		
		$tb_hslfilter = new mytable(array('id'=>'tbserverside','width'=>'100%'),$jdl_tb,$dt_tb,'');

		$html_txt .= $tb_hslfilter->display();
		
		return $html_txt;
	} 
	
	function ss_viewdata($param){
	    $dt_data = new dt_data;
		$data = $dt_data->getdtedit($param['idkec'],$param['iddesa'],$param['iddusun'],$param['idrt'],(intval($param['iDisplayStart'])/intval($param['iDisplayLength']))+1,intval($param['iDisplayLength']),$param['sSearch'],array($param['iSortCol_0'],$param['sSortDir_0']));
				
		   $totalrecords=$data['totaldata'];
           $totaldisplayrecords=$data['displaydata'];

           $output = array('sEcho' => intval($param['sEcho']),
                    'iTotalRecords' => $totalrecords,
                    'iTotalDisplayRecords' => $totaldisplayrecords,
                    'aaData'=>array()   
            );

      if(!empty($data['data']))
      {
         foreach ($data['data'] as $row) {
			 
            $output['aaData'][]=$row;
         }
      }

      return $output;
	
	}
	

	function hapus_data($kki)
	{
		$dt = new dt_family;
		if($dt->kki_exist($kki)==1){  
			$tmp=$this->view_data($kki)."<br><center><input type='submit' value='Hapus Data Keluarga' id='hapus_data' onClick='hapus_data($kki)' ></center>";
		}else{
			$tmp="<center>No. Kode Keluarga Indonesia (KKI) $kki Tidak Ada Didatabase</center>";
		}
		return $tmp;
	}

	function db_hapus_data($kki)
	{
		$dt_fam = new dt_family;
		$dt_indv=new dt_individu;
		$dt_ind_ks=new dt_fam_ind_detail;

		$dt_fam->delete_data(array('Kd_fam'=>$kki));
		$dt_indv->delete_data("Kd_fam='$kki'");
		$dt_ind_ks->delete_data(array('Kd_fam'=>$kki));
		
		return "<center>No. Kode Keluarga Indonesia (KKI) $kki Dihapus Dari Didatabase</center>";
	}

	function edit_hapus_data($idkec,$iddesa,$iddusun,$idrt,$kki)
	{
		$dt_fam = new dt_family;
		$dt_indv=new dt_individu;
		$dt_ind_ks=new dt_fam_ind_detail;

		$dt_fam->delete_data(array('Kd_fam'=>$kki));
		$dt_indv->delete_data("Kd_fam='$kki'");
		$dt_ind_ks->delete_data(array('Kd_fam'=>$kki));
		
		return $this->tb_edt_data($idkec,$iddesa,$iddusun,$idrt);  
	}

	function tambah_row($i)
	{
		$tb_fammbrtyp = new tb_gen('dbo_fam_mbr_typ');
		$tb_gender = new tb_gen('dbo_gender');
		$tb_martlstat = new tb_gen('dbo_martl_stat');
		$tb_mutasi = new tb_gen('dbo_mutasi');

		$dt_empmntstat = new dt_empmnt_stat;
		$dt_edulvl = new dt_edu_lvl;

		$mycmb=new mycmb;

		return "<tr>
			<td align='center'><input type='text' id='kak$i' name='indv[$i][kak]' size='7' maxlength='7' onkeypress='return isNumberKey(event)' ></td>   
			<td align='center'><input type='text' id='nm$i' name='indv[$i][nm]'></td>
			<td align='center'><select id='hub$i' name='indv[$i][hub]' onChange='bg_wrn_slct($i)' >".$mycmb->cmb_hbkk($tb_fammbrtyp->getData(''),3)."</select></td>
			<td align='center'><select id='jk$i' name='indv[$i][jk]' >".$mycmb->cmb_jk($tb_gender->getData(''),1)."</select></td>
			<td align='center'><input type='text' id='tpt_lhr$i' name='indv[$i][tpt_lhr]' size='20' ></td>
			<td align='center'><input type='text' id='tlhr$i' name='indv[$i][tlhr]' size='10' maxlength = '10' onkeypress='return isNumberKey1(event)' onKeyUp='tlhr_change(event,this,$i)' ><div id='div_pos_yd$i'></div></td>
			<td align='center'><select id='pkr$i' name='indv[$i][pkr]' >".$mycmb->cmb_kerja($dt_empmntstat->getdata(''))."</select></td>
			<td align='center'><select id='pdk$i' name='indv[$i][pdk]'>".$mycmb->cmb_edu($dt_edulvl->getdata(''))."</select></td>
			<td align='center'><select id='sts_mtr$i' name='indv[$i][sts_mtr]' >".$mycmb->cmb_stat($tb_martlstat->getData(''),1)."</select></td>
			<td align='center'><select id='mts$i' name='indv[$i][mts]' onChange='mts_change($i)' >".$mycmb->cmb_mutasi($tb_mutasi->getData(''))."</select></td>
			<td align='center'><input type='text' id='ket$i' name='indv[$i][ket]'  ></td>
			</tr>";
	}

	
  function save_fam($fam,$fsave)
  {
	  if(!empty($fam))
		{
			$dt_fam = new dt_family;

			$prop='10';
			$kab_kota='1017';
			$kec=$fam['kec'];
			$kel=$fam['desa'];
			$rw=$fam['dusun'];
			$rt=$fam['rt'];

			$pus=$fam['pus'];
			$btm=$fam['btm'];
			$almt=$fam['almt'];
			$komp=$fam['komp'];
			$pref =$fam['pref']; 
			$preflama = isset($fam['preflama']) ? $fam['preflama'] : ''; 
			$kki = $fam['pref'].$fam['kki'];
			$kkilama =$preflama.(isset($fam['kkilama']) ? $fam['kkilama'] : '');
			$kki_unik = $fam['kki'];  
			

			$fam_sql_arr= array('Kd_fam'=>$kki,
			'Kd_prop'=>$prop,
			'Kd_dist'=>$kab_kota,
			'Kd_subdist'=>$kec,
			'Kd_vill'=>$kel,
			'Kd_subvill'=>$rw,
			'Kd_neigh'=>$rt,
			'alamat'=>$almt,
			'komplek'=>$komp,
			'pus'=>$pus,
			'Bantuan_modal'=>$btm,
			'Kd_unik_fam'=>$kki_unik);
			
			$fam_sql_str= "Kd_fam='$kki',
					Kd_prop='$prop',
					Kd_dist='$kab_kota',
					Kd_subdist='$kec',
					Kd_vill='$kel',
					Kd_subvill='$rw',
					Kd_neigh='$rt', 
					alamat='$almt',
					komplek='$komp',
					pus='$pus',
					Bantuan_modal='$btm',
					Kd_unik_fam='$kki_unik'";
			
			
			if($pus!=0)
			{
				$kb=$fam['kb'];
				if($kb==1)
				{
					$src=$fam['src'];            
					$alt_kb = $fam['alt_kb'];
					
					$tgl_kb = $fam['tkont'];
					$t=explode('-',$tgl_kb);         
					$tgl_kb=$t[2]."-".$t[1]."-".$t[0];
					
					$fam_sql_arr['Kd_consrc']=$src;
					$fam_sql_arr['Kd_contyp']=$alt_kb;
					$fam_sql_arr['tgl_kb']=$tgl_kb;

                    $fam_sql_str.= ",Kd_consrc='$src',
							Kd_contyp='$alt_kb',
							tgl_kb='$tgl_kb'";					
					
					if($alt_kb==4)
					{
						$ipl = $fam['ipl'];
						$fam_sql_arr['Kd_implan']=$ipl;  
                        $fam_sql_str.= ",Kd_implan='$ipl'"; 						
					}else{
						//$fam_sql_arr['Kd_implan']=null;
						$fam_sql_str.= ",Kd_implan=NULL";
					}
                    $fam_sql_str.= ",Kd_nonacptr=NULL";					

				}elseif ($kb==0) {
					$s_bkb = $fam['s_bkb'];
					$fam_sql_arr['Kd_nonacptr']=$s_bkb;
					$fam_sql_str.= ",Kd_nonacptr='$s_bkb'";
				}else{
					//$fam_sql_arr['Kd_nonacptr']=null;
					$fam_sql_str.= ",Kd_nonacptr=NULL";  
				}

			}else{
				//$fam_sql_arr['Kd_nonacptr']=null;
				//$fam_sql_arr['Kd_implan']=null;
				//$fam_sql_arr['Kd_consrc']=null;
				//$fam_sql_arr['Kd_contyp']=null;
				//$fam_sql_arr['tgl_kb']=null;
				
				$fam_sql_str.= ",Kd_nonacptr=NULL,
						Kd_consrc=NULL,
						Kd_contyp=NULL,
						Kd_implan=NULL,
						tgl_kb=NULL";
			}
			
			$this->$fsave($fam_sql_arr,$fam_sql_str,$kki,$kkilama);
			
		    return array('rt'=>$rt,'pref'=>array('baru'=>$pref,'lama'=>$preflama),'kki'=>array('baru'=>$kki,'lama'=>$kkilama),'str'=>$fam_sql_str,'arr'=>$fam_sql_arr);
		
		}
		
		return array();
  }
  
  
  function save_indv($indv,$rt,$pref,$preflama,$kki,$kkilama,$fsave)
  {
	  if(!empty($indv))
		{
			$dt_indv=new dt_individu;
			
			foreach ($indv as $row) {
				if(!empty($row['kak'])){ 
					
					$kak=$row['kak'];
					$kaklama = isset($row['kaklama']) ? $row['kaklama'] : '';
					$nm=$row['nm'];
					$hub=$row['hub'];         
					$jk=$row['jk'];
					$tlhr=$row['tlhr'];
					$pkr=$row['pkr'];
					$pdk=$row['pdk'];      
					$sts=$row['sts_mtr'];      
					
					$tpt=$row['tpt_lhr'];
					$t=explode('-',$tlhr);         
					$tlhr=$t[2]."-".$t[1]."-".$t[0];					

					$tmp_arr =array('Kd_fam'=>$kki,
					'Kd_indv'=>$pref.$kak,
					'Kd_neigh'=>$rt,
					'Kd_fammbrtyp'=>$hub,
					'Nama'=>$nm,
					'Kd_gen'=>$jk,
					'Tgl_lahir'=>$tlhr,
					'Tpt_lahir'=>$tpt,
					'Kd_edu'=>$pdk,
					'Kd_martl'=>$sts,
					'Kd_emp'=>$pkr,
					'Kd_unik_indv'=>$kak); 
					
					
					$tmp_txt ="";
					if($kki!=$kkilama){
						$tmp_txt ="Kd_fam='$kki',";
					}

					if($kak!=$kaklama){
						$tmp_txt .="Kd_indv='".$pref.$kak."',";
					}

					$tmp_txt .="Kd_neigh='$rt',
					Kd_fammbrtyp='$hub',
					Nama='$nm',
					Kd_gen='$jk',
					Tgl_lahir='$tlhr',
					Tpt_lahir='$tpt',
					Kd_edu='$pdk',
					Kd_martl='$sts',
					Kd_emp='$pkr',
					Kd_unik_indv='".$kak."'";

					if(!empty($row['yd']))
					{
						$tmp_arr['Posyandu']=$row['yd'];
						$tmp_txt.=",Posyandu='$row[yd]'";
					}else{
						//$tmp_arr['Posyandu']=null;
						$tmp_txt.=",Posyandu=Null"; 
					}

					if(!empty($row['mts']))
					{
						$tmp_arr['Kd_mutasi']=$row['mts'];
						$tmp_txt.=",Kd_mutasi='$row[mts]'";
					}else{
						//$tmp_arr['Kd_mutasi']=null;
						$tmp_txt.=",Kd_mutasi=Null";
					}

					if(!empty($row['ket']))
					{
						$tmp_arr['Keterangan']=$row['ket'];
						$tmp_txt.=",Keterangan='$row[ket]'";
					}else{
						//$tmp_arr['Keterangan']=null;
						$tmp_txt.=",Keterangan=Null";
					}
					
					$this->$fsave($tmp_arr,$tmp_txt,$pref,$preflama,$kki,$kkilama,$kak,$kaklama);

				}
			}
			
		}
  }
  
  function save_ind_ks($ind_ks,$kki,$kkilama,$fsave)
  {
	  if(!empty($ind_ks))
		{
			$dt_ind_ks=new dt_fam_ind_detail;
			foreach ($ind_ks as $key => $value) {
				$tmp_arr = array('Kd_fam'=>$kki,
				'id_ind_ks'=>$key,
				'kd_prospinstat'=>$value);
				
				if($kkilama==$kki){
					$tmp_txt = "kd_prospinstat='$value'";					       
				}else{
					$tmp_txt = "Kd_fam='$kki',id_ind_ks='$key',kd_prospinstat='$value'";					
				} 
				$this->$fsave($tmp_arr,$tmp_txt,$kki,$kkilama,$key);       
			}
			
			$dt_kat = new dt_kategori;
			$dt_ind_ks = new dt_indikator_ks;
			$ketemu=true;  
			$qr=$dt_kat->getdata('');
			
			if(!empty($qr)){ 
				$jml_qr = count($qr);
				$i=0;
				while(($i<$jml_qr) AND $ketemu)
				{   
					
					$qrr=$dt_ind_ks->getdata("id_ind_ks_idk_1='".$qr[$i]['id_ind_ks']."'");
					if(!empty($qrr)){
						$jml_qrr = count($qrr);
						$j=0;
						while(($j<$jml_qrr) AND $ketemu)
						{
							$idh=$qrr[$j]['id_ind_ks'];
							if(isset($ind_ks[$idh]))
							{                      
								$isi=$ind_ks[$idh]; 
								
								if($isi==$qr[$i]['Kd_prospinstat'])
								{
									$sts_ks=$qr[$i]['Kd_prosplvl'];
									$ketemu=false;                              
								}      
							}
							$j++;  
						}
					}  
					$i++;   
				}
			}  
			$sts_ks=$ketemu ? 5 : $sts_ks;        
			$dt_fam = new dt_family;
			$dt_fam->updatedata1(array('Kd_prosplvl'=>$sts_ks,'Kd_fam'=>$kki));  
		}	
  }
  
  function finsert_fam($fam_sql_arr,$fam_sql_str,$kki,$kkilama)
  {
	 $dt_fam = new dt_family;
	 $dt_fam->insert_data($fam_sql_arr); 
  }  
  
  function finsert_indv($fam_sql_arr,$fam_sql_str,$pref,$preflama,$kki,$kkilama,$kak,$kaklama)
  {
	 $dt_indv=new dt_individu;
	 $dt_indv->insert_data($fam_sql_arr);	 
  }
  
  function finsert_ind_ks($fam_sql_arr,$fam_sql_str,$kki,$kkilama,$key)
  {
	 $dt_ind_ks=new dt_fam_ind_detail;
	 $dt_ind_ks->insert_data($fam_sql_arr); 
  }
  
   function insert_data($fam,$indv,$ind_ks)
	{
		$tmp=$this->save_fam($fam,'finsert_fam');
		$this->save_indv($indv,$tmp['rt'],$tmp['pref']['baru'],$tmp['pref']['lama'],$tmp['kki']['baru'],$tmp['kki']['lama'],'finsert_indv');
		$this->save_ind_ks($ind_ks,$tmp['kki']['baru'],$tmp['kki']['lama'],'finsert_ind_ks');
		return $this->after_tambah_data($tmp['kki']['baru']);
	}
	
  function fupdate_fam($fam_sql_arr,$fam_sql_str,$kki,$kkilama)
  {
	 $dt_fam = new dt_family;
	 $dt_fam->updatedata($fam_sql_str,"Kd_fam='$kkilama'");
  }  
  
  function fupdate_indv($fam_sql_arr,$fam_sql_str,$pref,$preflama,$kki,$kkilama,$kak,$kaklama)
  {
	                $dt_indv=new dt_individu;
	                
					if($kaklama!='')
					{
						
						$where='';  
						if($kki!=$kkilama){
							$where = "Kd_fam='$kkilama'"; 
						}
						if($kak!=$kaklama){
							$where .= (!empty($where) ? ' and ':'')."Kd_indv='".$preflama.$kaklama."'";
						}else{
							$where .= "Kd_indv='".$preflama.$kaklama."'";
						} 

						$dt_indv->updatedata($fam_sql_str,$where); 

					}else{
						$dt_indv->insert_data($fam_sql_arr); 
					}	 
  }
  
function fupdate_ind_ks($fam_sql_arr,$fam_sql_str,$kki,$kkilama,$key)
{
	$dt_ind_ks=new dt_fam_ind_detail;
	if($kkilama==$kki){					
		$dt_ind_ks->updatedata($fam_sql_str,"Kd_fam='$kki' and id_ind_ks='$key'");        
	}else{					
		$dt_ind_ks->updatedata($fam_sql_str,"Kd_fam='$kkilama'");
	} 
}

	function update_data($fam,$indv,$ind_ks)
	{
		$tmp=$this->save_fam($fam,'fupdate_fam');
		$this->save_indv($indv,$tmp['rt'],$tmp['pref']['baru'],$tmp['pref']['lama'],$tmp['kki']['baru'],$tmp['kki']['lama'],'fupdate_indv');
		$this->save_ind_ks($ind_ks,$tmp['kki']['baru'],$tmp['kki']['lama'],'fupdate_ind_ks');
		return $this->after_update_data($tmp['kki']['baru']);
	}
	
	function edit_data($fam,$indv,$ind_ks)
	{
		$tmp=$this->save_fam($fam,'fupdate_fam');
		$this->save_indv($indv,$tmp['rt'],$tmp['pref']['baru'],$tmp['pref']['lama'],$tmp['kki']['baru'],$tmp['kki']['lama'],'fupdate_indv');
		$this->save_ind_ks($ind_ks,$tmp['kki']['baru'],$tmp['kki']['lama'],'fupdate_ind_ks');
		return $tmp['kki']['baru'];
	}

}	

?>