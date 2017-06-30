<?php

class mycmb {

   public function cmb_kec($data=array(),$first='Semua Kecamatan',$kdselected='')
   {

      $temp = "<option value=''>-- $first --</option>";
	  if(!empty($data)){    
	      foreach($data as $row)
	      {
	          $selected= (!empty($kdselected) and ($row['id_unit_detail']==$kdselected))  ? 'selected' : '';
            $temp.="<option value='$row[id_unit_detail]' $selected >$row[no_unit_detail]</option>";
	      }
      }
      return $temp;
   } 

   public function cmb_desa($data=array(),$first='Semua Desa/Kelurahan',$kdselected='')
   {

      $temp = "<option value=''>-- $first --</option>";
     if(!empty($data)){    
         foreach($data as $row)
         {
             $selected= (!empty($kdselected) and ($row['id_unit_detail']==$kdselected))  ? 'selected' : '';
             $temp.="<option value='$row[id_unit_detail]' $selected >$row[no_unit_detail]</option>";
         }
      }
      return $temp;
   }

   public function cmb_dusun($data=array(),$first='Semua Dusun/RW',$kdselected='')
   {

      $temp = "<option value=''>-- $first --</option>";
     if(!empty($data)){    
         foreach($data as $row)
         {
             $selected= (!empty($kdselected) and ($row['id_unit_detail']==$kdselected))  ? 'selected' : '';
             $temp.="<option value='$row[id_unit_detail]' $selected >$row[no_unit_detail]</option>";
         }
      }
      return $temp;
   }

   public function cmb_rt($data=array(),$first='Semua RT',$kdselected='')
   {

      $temp = "<option value=''>-- $first --</option>";
     if(!empty($data)){    
         foreach($data as $row)
         {
             $selected= (!empty($kdselected) and ($row['id_unit_detail']==$kdselected))  ? 'selected' : '';
             $temp.="<option value='$row[id_unit_detail]' $selected >$row[no_unit_detail]</option>";
         }
      }
      return $temp;
   }

   public function cmb_hbkk($data=array(),$kdselected='')
   {
     $temp = '';
     if(!empty($data)){    
         foreach($data as $row)
         {
             $selected= (!empty($kdselected) and ($row['Kd_fammbrtyp']==$kdselected))  ? 'selected' : '';
             $temp.="<option value='$row[Kd_fammbrtyp]' $selected>$row[Nm_fammbrtyp_ind]</option>";
         }
      }
      return $temp;
   }

   public function cmb_jk($data=array(),$kdselected='')
   {
     $temp = '';
     if(!empty($data)){    
         foreach($data as $row)
         {
             $selected= (!empty($kdselected) and ($row['Kd_gen']==$kdselected))  ? 'selected' : '';
             $temp.="<option value='$row[Kd_gen]' $selected>$row[Nm_gen_ind]</option>";
         }
      }
      return $temp;
   }

   public function cmb_kerja($data=array(),$kdselected='')
   {
     $temp = '';
     if(!empty($data)){    
         foreach($data as $row)
         {
             $selected= (!empty($kdselected) and ($row['Kd_emp']==$kdselected))  ? 'selected' : '';
             $temp.="<option value='$row[Kd_emp]' $selected>$row[Nm_emp_ind]</option>";
         }
      }
      return $temp;
   }

   public function cmb_edu($data=array(),$kdselected='')
   {
     $temp = '';
     if(!empty($data)){    
         foreach($data as $row)
         {
             $selected= (!empty($kdselected) and ($row['Kd_edu']==$kdselected))  ? 'selected' : '';
             $temp.="<option value='$row[Kd_edu]' $selected>$row[Nm_edu_ind]</option>";
         }
      }
      return $temp;
   }

   public function cmb_stat($data=array(),$kdselected='')
   {
     $temp = '';
     if(!empty($data)){    
         foreach($data as $row)
         {
             $selected= (!empty($kdselected) and ($row['Kd_martl']==$kdselected))  ? 'selected' : '';
             $temp.="<option value='$row[Kd_martl]' $selected>$row[Nm_martl_ind]</option>";
         }
      }
      return $temp;
   }

   public function cmb_mutasi($data=array(),$kdselected='')
   {
     $temp = "<option value='' ></option>";
     if(!empty($data)){    
         foreach($data as $row)
         {
             $selected= (!empty($kdselected) and ($row['Kd_mutasi']==$kdselected))  ? 'selected' : '';
             $temp.="<option value='$row[Kd_mutasi]' $selected>$row[Nm_mutasi]</option>";
         }
      }
      return $temp;
   }

  public function cmb_contyp($data=array(),$kdselected='')
   {
     $temp = '';
     if(!empty($data)){    
         foreach($data as $row)
         {
             $selected= (!empty($kdselected) and ($row['Kd_contyp']==$kdselected))  ? 'selected' : '';
             $temp.="<option value='$row[Kd_contyp]' $selected>$row[Nm_contyp_ind]</option>";
         }
      }
      return $temp;
   }

   public function cmb_nonkb($data=array(),$kdselected='')
   {
     $temp = '';
     if(!empty($data)){    
         foreach($data as $row)
         {
             $selected= (!empty($kdselected) and ($row['Kd_nonacptr']==$kdselected))  ? 'selected' : '';
             $temp.="<option value='$row[Kd_nonacptr]' $selected>$row[Nm_nonacptr_ind]</option>";
         }
      }
      return $temp;
   }

}

?>