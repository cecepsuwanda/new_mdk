<?php

class html_element {
  
  private function addAttributes( $attr_ar ) {
        $str = '';
        // check minimized attributes
        $min_atts = array('checked', 'disabled', 'readonly', 'multiple');
        foreach( $attr_ar as $key=>$val ) {
            if ( in_array($key, $min_atts) ) {
                if ( !empty($val) ) { 
                    $str .= " $key=\"$key\"";
                }
            } else {
                $str .= " $key=\"$val\"";
            }
        }
        return $str;
    }
    
   public function addfieldset($legend,$data, $attr_ar_leg = array(), $attr_ar = array()) {
        $str = "<fieldset ";
        if ($attr_ar) {
            $str .= $this->addAttributes( $attr_ar );
        }
        $str.='>';
		if(!empty($legend)){
		  $str .='<legend ';
          if ($attr_ar_leg) {
            $str .= $this->addAttributes( $attr_ar_leg );
          }		  
		  $str .='> '.$legend.' </legend>';	
		}
		$str .='<div>'.$data.'</div> </fieldset>';
        return $str;
    }


    public function addol($data) {
        $str = "<ol>";
        
		if(!empty($data))
		{
          foreach($data as $row)
          {
           $str .="<li>".$row."</li>";
          } 		  
        }			
		$str .="</ol>";
        return $str;
    }
 }

?>