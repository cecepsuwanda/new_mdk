var dlg_edit, dlg_view;

function tambah_baris() {
	jmlbrs = $("#tbindv tr").size();

	if (jmlbrs > 4) {
		$("#tbindv tr").each(function (index, value) {
			alert(index + ' ' + this.name);
		});
	}

	data = 'action=menu&istmbhrw=1&menu_lvl=' + menu_lvl + '&menu_idx=' + menu_idx + '&menu_idx1=' + menu_idx1 + '&menu_idx2=' + menu_idx2 + '&menu_idx3=' + menu_idx3;
	data = data + '&jmlbrs=' + jmlbrs;
	myajax_cmb('', data, null, function (data) {
		$("#tbindv tbody").append(data);
	});

}

function proc_pus(t) {
	if (t.value == 0) {
		$("#row_kb").hide();
		$("#row_src").hide();
		$("#row_alt_kb").hide();
		$("#row_tkont").hide();
		$("#row_s_bkb").hide();
		$("#row_ipl").hide();
	} else {
		if (t.value == 1) {
			$("#row_kb").show();
		}
	}
}

function proc_kb(t) {

	if (t.value == 0) {
		$("#row_src").hide();
		$("#row_alt_kb").hide();
		$("#row_tkont").hide();
		$("#row_ipl").hide();
		$("#row_s_bkb").show();
	} else {
		if (t.value == 1) {
			$("#row_src").show();
			$("#row_alt_kb").show();
			$("#row_tkont").show();
			$("#row_s_bkb").hide();
		}
	}
}

function cek_input() {

	if ($('#almt').val() == '') {
		alert("Field Alamat Tidak boleh Kosong");
		$('#almt').focus();
		return false;
	} else if ($('#kec').val() == '') {
		alert("Pilih Kecamatan Terlebih Dahulu");

		return false;
	} else if ($('#desa').val() == '') {
		alert("Pilih Desa/Kelurahan Terlebih Dahulu");

		return false;
	} else if ($('#dusun').val() == '') {
		alert("Pilih Dusun/RW Terlebih Dahulu");

		return false;
	} else if ($('#rt').val() == '') {
		alert("Pilih RT Terlebih Dahulu");

		return false;
	} else if ($('#kki').val() == '') {
		alert("Isi Nomor Kode Keluarga Indonesia (KKI) Terlebih Dahulu");
		$('kki').select();
		return false;
	} else if ($('#kki').val().length != 7) {
		alert("Jumlah Digit/Karakter Nomor Kode Keluarga Indonesia (KKI) Harus Sama Dengan Tujuh (7)");
		$('#kki').select();
		return false;
	}

	var ada_kbr = false;
	if ($('#kak1').val() == '') {
		alert("Kode Anggota Keluarga Harus Diisi");
		$('#kak1').focus();
		return false;
	}

	var jmlbrs = $("#tbindv tbody tr").size();
	for (var i = 1; i <= jmlbrs; i++) {
		if ($('#kak' + i).val() != '') {
			if ($('#nm' + i).val() == '') {

				alert("Nama Anggota Keluarga Harus Diisi");

				$('#nm' + i).focus();
				return false;

			}
		} else {
			break;
		}
	}

	var arr_kk_kpl = new Array();
	var idx_kk_kpl = 0;
	for (var i = 2; i <= jmlbrs; i++) {
		if ($('#kak' + i).val() != '') {
			var tmp = $('#hub' + i + ' option:selected').val();
			var tmp1 = $('#mts' + i + ' option:selected').val();

			if (tmp == 1 && tmp1 == '') {
				arr_kk_kpl[idx_kk_kpl] = i;
				idx_kk_kpl++;
			}
		} else {
			break;
		}
	}

	var tmp1 = $('#mts1' + ' option:selected').val();
	if (arr_kk_kpl.length > 0 && tmp1 == '') {
		alert("Hubungan Dengan KK 'KEPALA KELURAGA' Tidak Boleh Lebih Dari Satu ");
		return false;
	} else if (arr_kk_kpl.length > 1) {
		alert("Hubungan Dengan KK 'KEPALA KELURAGA' Tidak Boleh Lebih Dari Satu ");
		return false;
	} else if (arr_kk_kpl.length == 0 && tmp1 != 0) {
		alert("Hubungan Dengan KK 'KEPALA KELURAGA' Harus Ada Di Data Anggota Keluarga");
		return false;
	}

	for (var i = 1; i <= jmlbrs; i++) {
		if ($('#kak' + i).val() != '') {
			if ($('#tpt_lhr' + i).val() == '') {
				alert("Tempat Lahir Anggota Keluarga Harus Diisi");

				$('#tpt_lhr' + i).focus();
				return false;
			}
		} else {
			break;
		}
	}

	for (var i = 1; i <= jmlbrs; i++) {
		if ($('#kak' + i).val() != '') {
			if ($('#tlhr' + i).val() == '') {
				alert("Tanggal Lahir Anggota Keluarga Harus Diisi");
				$('#tlhr' + i).focus();
				return false;
			}
		} else {
			break;
		}
	}

	for (var i = 1; i <= jmlbrs; i++) {
		if ($('#kak' + i).val() != '') {
			if ($('#tlhr' + i).val() != '') {

				if (prosesformattgl($('#tlhr' + i).val()) == false) {
					$('#tlhr' + i).focus();
					return false;
				}
			}
		} else {
			break;
		}
	}

	for (var i = 1; i <= jmlbrs; i++) {
		if ($('#kak' + i).val() != '') {
			if ($('#tlhr' + i).val() != '') {

				if ((prosestglpos($('#tlhr' + i).val()) == true) && (cek_pos_yandu1(i) == true)) {
					if ($('#yd' + i + ':checked').length == 0) {
						alert("Ikut Program Posyandu Harus Dipilih");
						return false;
					}
				}
			}
		} else {
			break;
		}
	}

	for (var i = 1; i < jmlbrs; i++) {

		var k = 2;
		for (var j = i + 1; j <= jmlbrs; j++) {

			if ($('#kak' + i).val() != '') {
				if ($('#kak' + i).val() == $('#kak' + j).val()) {
					alert(i + ' ' + $('#kak' + i).val() + ' ' + j + ' ' + $('#kak' + j).val());
					ada_kbr = true;
					k++;
				}
			}

		}

		if (ada_kbr)
			break;
	}

	if (ada_kbr) {
		alert("Terdapat Nomor Kode Anggota Keluarga KAK Yang Sama");
		return false;
	}

	if ($('#btm:checked').length == 0) {
		alert("Bantuan Modal Harus Dipilih");
		return false;
	} else if ($('#pus:checked').length == 0) {
		alert("PUS Harus Dipilih");
		return false;
	} else if ($('#pus:checked').val() == 1) {
		if ($('#kb:checked').length == 0) {
			alert("Pilih Option Peserta KB/Bukan Peserta KB Terlebih Dahulu");
			return false;
		} else if ($('#kb:checked').val() == 1) {
			var sli = document.getElementById('alt_kb').selectedIndex;

			if (document.getElementById('alt_kb').options[sli].text.toLowerCase() == 'implant') {
				var cek_impl = $('#ipl:checked').length > 0;

			} else
				var cek_impl = true;

			var cek = $('#src:checked').length > 0;

			if (!cek) {
				alert("Pilih Tempat Pelayanan KB (Pemerintah/Swasta) Terlebih Dahulu");
				return false;
			} else if (!cek_impl) {
				alert("Pilih Implan Terlebih Dahulu");
				return false;
			} else if ($('#tkont').val() == '') {
				alert("Isi Tanggal Kapan Menjadi Peserta KB Terlebih Dahulu (Metode Kontrasepsi Yang Terakhir Dipakai)");
				$('#tkont').focus();
				return false;
			} else if ($('#tkont').val() != '') {

				if (prosesformattgl($('#tkont').val()) == false) {
					$('#tkont').focus();
					return false;
				}
			}

		}
	}

	var jml_radio = $("input[id^='ind_ks_']").length / 4;
	var jml_radio_check = $("input[id^='ind_ks_']:checked").length;

	if (jml_radio != jml_radio_check) {
		alert("Data Indikator Dan Status Tahapan Keluarga Tidak Lengkap");
		return false;
	}

	return true;
}

var tandagaris = "-";

function hariArray(n) {
	for (var i = 1; i <= n; i++) {
		this[i] = 31
			if (i == 4 || i == 6 || i == 9 || i == 11) {
				this[i] = 30
			}
			if (i == 2) {
				this[i] = 29
			}
	}
	return this
}

function okIntegerlah(s) {
	var i;
	for (i = 0; i < s.length; i++) {

		var c = s.charAt(i);
		if (((c < "0") || (c > "9")))
			return false;
	}
	// All characters are numbers.
	return true;
}

function hapusspasichars(s, bag) {
	var i;
	var returnString = "";

	for (i = 0; i < s.length; i++) {
		var c = s.charAt(i);
		if (bag.indexOf(c) == -1)
			returnString += c;
	}
	return returnString;
}

function hariInFebruary(year) {

	return (((year % 4 == 0) && ((!(year % 100 == 0)) || (year % 400 == 0))) ? 29 : 28);
}

function prosesformattgl(dtStr) {

	var splt_tgl = dtStr.split("-");
	var sts_thn = false;
	var tgl_skrg = new Date();
	var bln = tgl_skrg.getMonth() + 1;
	var tgl = tgl_skrg.getDate();
	var thn = tgl_skrg.getFullYear();

	if (parseInt(eval(splt_tgl[2])) > thn) {
		sts_thn = true;
	} else if (parseInt(eval(splt_tgl[2])) == thn) {
		if (parseInt(eval(splt_tgl[1])) > bln)
			sts_thn = true;
		else if (parseInt(eval(splt_tgl[1])) == bln) {
			if (parseInt(eval(splt_tgl[0])) > tgl)
				sts_thn = true;
		}
	}

	var daysInMonth = hariArray(12)
		var pos2 = dtStr.indexOf(tandagaris)
		var pos1 = dtStr.indexOf(tandagaris, pos2 + 1)
		var strDay = dtStr.substring(0, pos1)
		var strMonth = dtStr.substring(pos2 + 1, pos1)
		var strYear = dtStr.substring(pos1 + 1)
		strYr = strYear
		if (strDay.charAt(0) == "0" && strDay.length > 1)
			strDay = strDay.substring(1)
				if (strMonth.charAt(0) == "0" && strMonth.length > 1)
					strMonth = strMonth.substring(1)
						for (var i = 1; i <= 3; i++) {
							if (strYr.charAt(0) == "0" && strYr.length > 1)
								strYr = strYr.substring(1)
						}
						month = parseInt(strMonth)
						day = parseInt(strDay)
						year = parseInt(strYr)
						var validformat = /^\d{2}\-\d{2}\-\d{4}$/
						var validformat1 = /^\d{1}\-\d{2}\-\d{4}$/
						var validformat2 = /^\d{2}\-\d{1}\-\d{4}$/
						var validformat3 = /^\d{1}\-\d{1}\-\d{4}$/
						var returnval = false
						if (!validformat.test(dtStr) && !validformat1.test(dtStr) && !validformat2.test(dtStr) && !validformat3.test(dtStr)) {
							alert("Format Tanggal Tidak Valid, Contoh Format Tanggal Valid (tgl-bln-thn) : 01-01-2001, 01-1-2001, 1-01-2001, 1-1-2001 ");

							return false
						}

						if (strDay.length < 1 || day < 1 || day > 31 || (month == 2 && day > hariInFebruary(year)) || day > daysInMonth[month]) {
							alert("Tanggal Yang Dimasukkan Tidak Valid")

							return false
						}
						if (strMonth.length < 1 || month < 1 || month > 12) {
							alert("Bulan Yang Dimasukkan Tidak Valid")

							return false
						}
						if (strYear.length != 4 || year == 0) {
							alert("Jumlah Digit Tahun Harus Sama Dengan 4")

							return false
						}
						if (dtStr.indexOf(tandagaris, pos1 + 1) != -1 || okIntegerlah(hapusspasichars(dtStr, tandagaris)) == false) {
							alert("Data Yang Dimasukkan Tidak Valid")

							return false
						}
						if (sts_thn) {
							alert("Tanggal Yang Dimasukkan (" + dtStr + ") Tidak boleh Lebih Besar Dari Tanggal Sekarang (" + tgl + "-" + bln + "-" + thn + ")");

							return false
						}
						return true
}

function prosestglpos(dtStr) {

	var splt_tgl = dtStr.split("-");
	var sts_thn = false;
	var tgl_skrg = new Date();
	var bln = tgl_skrg.getMonth() + 1;
	var tgl = tgl_skrg.getDate();
	var thn = tgl_skrg.getFullYear();

	if (parseInt(eval(splt_tgl[2])) > thn) {
		sts_thn = true;
	} else if (parseInt(eval(splt_tgl[2])) == thn) {
		if (parseInt(eval(splt_tgl[1])) > bln)
			sts_thn = true;
		else if (parseInt(eval(splt_tgl[1])) == bln) {
			if (parseInt(eval(splt_tgl[0])) > tgl)
				sts_thn = true;
		}
	}

	    var daysInMonth = hariArray(12)
		var pos2 = dtStr.indexOf(tandagaris)
		var pos1 = dtStr.indexOf(tandagaris, pos2 + 1)
		var strDay = dtStr.substring(0, pos1)
		var strMonth = dtStr.substring(pos2 + 1, pos1)
		var strYear = dtStr.substring(pos1 + 1)
		strYr = strYear
		if (strDay.charAt(0) == "0" && strDay.length > 1)
			strDay = strDay.substring(1)
				if (strMonth.charAt(0) == "0" && strMonth.length > 1)
					strMonth = strMonth.substring(1)
						for (var i = 1; i <= 3; i++) {
							if (strYr.charAt(0) == "0" && strYr.length > 1)
								strYr = strYr.substring(1)
						}
						month = parseInt(strMonth)
						day = parseInt(strDay)
						year = parseInt(strYr)
						var validformat = /^\d{2}\-\d{2}\-\d{4}$/
						var validformat1 = /^\d{1}\-\d{2}\-\d{4}$/
						var validformat2 = /^\d{2}\-\d{1}\-\d{4}$/
						var validformat3 = /^\d{1}\-\d{1}\-\d{4}$/
						var returnval = false
						if (!validformat.test(dtStr) && !validformat1.test(dtStr) && !validformat2.test(dtStr) && !validformat3.test(dtStr)) {
							return false;
						}

						if (strDay.length < 1 || day < 1 || day > 31 || (month == 2 && day > hariInFebruary(year)) || day > daysInMonth[month]) {
							return false;

						}
						if (strMonth.length < 1 || month < 1 || month > 12) {
							return false;

						}
						if (strYear.length != 4 || year == 0) {
							return false;

						}
						if (dtStr.indexOf(tandagaris, pos1 + 1) != -1 || okIntegerlah(hapusspasichars(dtStr, tandagaris)) == false) {
							return false;

						}
						if (sts_thn) {
							return false;

						}
						return true;
}

function cek_kki() {
	kki = $("#pref").val() + $("#kki").val();
	data = 'action=menu&iskkiexist=1&menu_lvl=' + menu_lvl + '&menu_idx=' + menu_idx + '&menu_idx1=' + menu_idx1 + '&menu_idx2=' + menu_idx2 + '&menu_idx3=' + menu_idx3;
	data = data + '&kki=' + kki;

	myajax_cmb('', data, null, function (data) {

		if (data == 1) {

			if ((menu_idx == 1 && menu_idx1 == 1) || (menu_idx == 1 && menu_idx1 == 3)) {
				kkilama = $("#preflama").val() + $("#kkilama").val();
				if (kki == kkilama) {
					cek_kak();
				} else {
					alert("NOMOR KKI " + kki + " SUDAH ADA DIDATABASE SILAHKAN DIULANGI !!!");
					$('#kki').select();
				}

			} else {
				alert("NOMOR KKI " + kki + " SUDAH ADA DIDATABASE SILAHKAN DIULANGI !!!");
				$('#kki').select();
			}

		} else {
			cek_kak();
		}

	});

}

function cek_kak() {
	data = 'action=menu&iskakexist=1&menu_lvl=' + menu_lvl + '&menu_idx=' + menu_idx + '&menu_idx1=' + menu_idx1 + '&menu_idx2=' + menu_idx2 + '&menu_idx3=' + menu_idx3;
	$("input[id^='kak']").each(function (index, value) {
		if (this.value != '') {
			if ((menu_idx == 1 && menu_idx1 == 1) || (menu_idx == 1 && menu_idx1 == 3)) {

				if (this.id.includes('kaklama')) {
					tmp = this.id.replace('kaklama', 'kak');
					tmpval = $("#" + tmp).val();
					if (this.value != tmpval) {
						data = data + '&' + this.name + '=' + $("#pref").val() + this.value;
					}
				} else {
					if (this.id.includes('kak')) {
						tmp = this.id.replace('kak', 'kaklama');
						tmpval = $("#" + tmp).val();
						if (this.value != tmpval) {
							data = data + '&' + this.name + '=' + $("#pref").val() + this.value;
						}
					} else {
						data = data + '&' + this.name + '=' + $("#pref").val() + this.value;
					}
				}
			} else {
				data = data + '&' + this.name + '=' + $("#pref").val() + this.value;
			}
		}
	});

	myajax_cmb('', data, null, function (data) {

		if (data != 0) {
			alert("NOMOR KAK " + $("#pref").val() + $("#kak" + data).val() + " SUDAH ADA DIDATABASE SILAHKAN DIULANGI !!!");
			$("#kak" + data).select();

		} else {
			if (menu_idx == 1 && menu_idx1 == 0) {
				add_data();
			} else {
				if (menu_idx == 1 && menu_idx1 == 1) {
					update_data();
				} else {
					if (menu_idx == 1 && menu_idx1 == 3) {
						edit_data();
					}
				}
			}
		}
	});

}

function getdisableddata(data)
{
	$("input[id^='kak']:disabled").each(function (index, value) {
		data = data + '&' + this.name + '=' + this.value;
	});

	$("input[id^='nm']:disabled").each(function (index, value) {
		data = data + '&' + this.name + '=' + this.value;
	});

	$("select[id^='jk']:disabled").each(function (index, value) {
		data = data + '&' + this.name + '=' + this.value;
	});

	$("input[id^='tpt_lhr']:disabled").each(function (index, value) {
		data = data + '&' + this.name + '=' + this.value;
	});

	$("input[id^='tlhr']:disabled").each(function (index, value) {
		data = data + '&' + this.name + '=' + this.value;
	});

	$("input[id^='yd']:disabled").each(function (index, value) {
		if (this.checked) {
			data = data + '&' + this.name + '=' + this.value;
		}

	});

	$("select[id^='pkr']:disabled").each(function (index, value) {
		data = data + '&' + this.name + '=' + this.value;
	});

	$("select[id^='pdk']:disabled").each(function (index, value) {
		data = data + '&' + this.name + '=' + this.value;
	});

	$("input[id^='ket']:disabled").each(function (index, value) {
		data = data + '&' + this.name + '=' + this.value;
	});

	$("select[id^='hub']:disabled").each(function (index, value) {
		data = data + '&' + this.name + '=' + this.value;
	});

	$("select[id^='sts_mtr']:disabled").each(function (index, value) {
		data = data + '&' + this.name + '=' + this.value;
	});
	
	
	return data;
}


function add_data() {
	data = 'action=menu&issave=1&menu_lvl=' + menu_lvl + '&menu_idx=' + menu_idx + '&menu_idx1=' + menu_idx1 + '&menu_idx2=' + menu_idx2 + '&menu_idx3=' + menu_idx3 + '&' + $('#frminput').serialize();
	data = data + '&fam[pref]=' + $("#pref").val();

	data=getdisableddata(data);
	
	myajax_cmb('', data, function () {
		$('#data').html("<font size='5' color='red'>Silahkan Tunggu, Sedang Proses ....<\/font> <img src='img/ajax-loader.gif' />");
	},
		function (data) {
		$('#data').html(data);
	});
}

function update_data() {

	data = 'action=menu&isupdate=1&menu_lvl=' + menu_lvl + '&menu_idx=' + menu_idx + '&menu_idx1=' + menu_idx1 + '&menu_idx2=' + menu_idx2 + '&menu_idx3=' + menu_idx3 + '&' + $('#frmupdate').serialize();
	data = data + '&fam[pref]=' + $("#pref").val();

	data=getdisableddata(data);
	
	myajax_cmb('', data, function () {
		$('#data').html("<font size='5' color='red'>Silahkan Tunggu, Sedang Proses ....<\/font> <img src='img/ajax-loader.gif' />");
	},
		function (data) {
		$('#data').html(data);
	});
}

function edit_data() {

	data = 'action=menu&isupdate=1&menu_lvl=' + menu_lvl + '&menu_idx=' + menu_idx + '&menu_idx1=' + menu_idx1 + '&menu_idx2=' + menu_idx2 + '&menu_idx3=' + menu_idx3 + '&' + $('#frmupdate').serialize();
	data = data + '&fam[pref]=' + $("#pref").val();

	data=getdisableddata(data);

	myajax_cmb('', data, null,
		function (data) {			
			dlg_edit.dialog("close");
			edt_view_data(data.trim());
		});
}

function hapus_data(kki) {
	var r = confirm("Yakin Ingin Menghapus No. Kode Keluarga Indonesia (KKI) " + kki + " ?");
	if (r == true) {
		data = 'action=menu&isdelete=1&menu_lvl=' + menu_lvl + '&menu_idx=' + menu_idx + '&menu_idx1=' + menu_idx1 + '&menu_idx2=' + menu_idx2 + '&menu_idx3=' + menu_idx3;
		data = data + '&kki=' + kki;
		myajax_filter(data);
	}
}

function edit_hapus_data(idkec, iddesa, iddusun, idrt, kki) {
	var r = confirm("Yakin Ingin Menghapus No. Kode Keluarga Indonesia (KKI) " + kki + " ?");
	if (r == true) {
		data = 'action=menu&isdelete=1&menu_lvl=' + menu_lvl + '&menu_idx=' + menu_idx + '&menu_idx1=' + menu_idx1 + '&menu_idx2=' + menu_idx2 + '&menu_idx3=' + menu_idx3;
		data = data + '&kki=' + kki + "&idkec=" + idkec + "&iddesa=" + iddesa + "&iddusun=" + iddusun + "&idrt=" + idrt;

		myajax_filter(data);
	}
}

function edt_view_data(kki) {
	data = 'action=menu&isview=1&menu_lvl=' + menu_lvl + '&menu_idx=' + menu_idx + '&menu_idx1=' + menu_idx1 + '&menu_idx2=' + menu_idx2 + '&menu_idx3=' + menu_idx3;
	data = data + '&kki=' + kki;
	myajax_cmb('dialog', data, null, function (data) {
		dlg_view = $('#dialog-view-' + kki).dialog({
				autoOpen : true,
				modal : true,
				width : 950,
				close : function () {
					$('#dialog-view-' + kki).empty();
					$('#dialog-view-' + kki).remove();
					$('#dialog-edit-' + kki).empty();
					$('#dialog-edit-' + kki).remove();					
					$(this).dialog("destroy");
					$(this).remove();
				},
				buttons : {
					"Tutup" : function () {
						$(this).dialog("close");
					}
				}
			});
	});
}

function edt_edit_data(kki) {
	data = 'action=menu&isedit=1&menu_lvl=' + menu_lvl + '&menu_idx=' + menu_idx + '&menu_idx1=' + menu_idx1 + '&menu_idx2=' + menu_idx2 + '&menu_idx3=' + menu_idx3;
	data = data + '&kki=' + kki;
	myajax_cmb('dialog', data, null, function (data) {
		dlg_edit = $('#dialog-edit-' + kki).dialog({
				autoOpen : true,
				modal : true,
				width : 1200,
				close : function () {
					$('#dialog-view-' + kki).empty();
					$('#dialog-view-' + kki).remove();
					$('#dialog-edit-' + kki).empty();
					$('#dialog-edit-' + kki).remove();					
					$(this).dialog("destroy");
					$(this).remove();
				},
				buttons : {
					"Update Data Keluarga" : function () {
						if (cek_input()) {
							cek_kki();
						}

					},
					"Tutup" : function () {
						$(this).dialog("close");
					}
				}
			});
	});
}

function form_add() {
	if (cek_input()) {
		cek_kki();
	}
}

function return_form_add() {
	var data = 'action=menu&nm_menu=' + menu_txt + '&menu_lvl=' + menu_lvl + '&menu_idx=' + menu_idx + '&menu_idx1=' + menu_idx1 + '&menu_idx2=' + menu_idx2 + '&menu_idx3=' + menu_idx3;
	myajax_cmb('content', data, null, bind_cmb);
}

function form_update() {
	if (cek_input()) {
		cek_kki();
	}
}

function return_form_update($kki) {
	data = 'action=menu&isfilter=1&menu_lvl=' + menu_lvl + '&menu_idx=' + menu_idx + '&menu_idx1=' + menu_idx1 + '&menu_idx2=' + menu_idx2 + '&menu_idx3=' + menu_idx3;
	data = data + '&kki=' + kki;
	myajax_filter(data);

}

function bg_wrn_slct(i) {
	var tmp = $('#hub' + i + ' option:selected').val();

	if (tmp != 2) {
		$('#sts_mtr' + i).prop('disabled', false);
	} else {
		$('#sts_mtr' + i).val('2');
		$('#sts_mtr' + i).prop('disabled', true);
	}

}

function proc_alt_kb(t) {
	var sli = t.selectedIndex;

	if (t.options[sli].text.toLowerCase() == 'implant') {
		$('#row_ipl').show();
	} else {
		$('#row_ipl').hide();
	}

}

function mts_change(i) {
	var tmp = $('#mts' + i + ' option:selected').val();

	if (tmp != '') {
		$('#kak' + i).prop('disabled', true);
		$('#nm' + i).prop('disabled', true);
		$('#hub' + i).prop('disabled', true);
		$('#jk' + i).prop('disabled', true);
		$('#tpt_lhr' + i).prop('disabled', true);
		$('#tlhr' + i).prop('disabled', true);

		$("input[id='yd" + i + "']").each(function (index, value) {
			this.disabled = true;
		});

		$('#pkr' + i).prop('disabled', true);
		$('#pdk' + i).prop('disabled', true);
		$('#sts_mtr' + i).prop('disabled', true);
		$('#ket' + i).prop('disabled', true);
	} else {
		$('#kak' + i).prop('disabled', false);
		$('#nm' + i).prop('disabled', false);
		if ((i != 1) || ($('#hub' + i + ' option:selected').val() != 1)) {
			$('#hub' + i).prop('disabled', false);
		}

		$('#jk' + i).prop('disabled', false);
		$('#tpt_lhr' + i).prop('disabled', false);
		$('#tlhr' + i).prop('disabled', false);

		$("input[id='yd" + i + "']").each(function (index, value) {
			this.disabled = false;
		});

		$('#pkr' + i).prop('disabled', false);
		$('#pdk' + i).prop('disabled', false);
		if ($('#hub' + i + ' option:selected').val() != 2) {
			$('#sts_mtr' + i).prop('disabled', false);
		}
		$('#ket' + i).prop('disabled', false);
	}

}

function tlhr_change(e, t, i) {
	var tmp = t.value;
	if (tmp.length == 10) {
		if (prosestglpos(tmp) == true) {
			cek_pos_yandu(i);
		}
	} else {
		$('#div_pos_yd' + i).hide();
	}
}

function cek_pos_yandu1(idx_pos) {
	var splt_tgl = $('#tlhr' + idx_pos).val().split("-");

	var tgl_skrg = new Date();
	var bln = tgl_skrg.getMonth() + 1;
	var tgl = tgl_skrg.getDate();
	var thn = tgl_skrg.getFullYear();

	if (parseInt(eval(splt_tgl[2])) == (thn - 5)) {
		if (parseInt(eval(splt_tgl[1])) == bln) {
			if (parseInt(eval(splt_tgl[0])) > tgl) {
				return true;
			} else
				return false;
		} else if (parseInt(eval(splt_tgl[1])) > bln) {
			return true;
		} else
			return false;
	} else if (parseInt(eval(splt_tgl[2])) > (thn - 5)) {
		return true;
	} else
		return false;

}

function cek_pos_yandu(idx_pos) {
	var splt_tgl = $('#tlhr' + idx_pos).val().split("-");

	var tgl_skrg = new Date();
	var bln = tgl_skrg.getMonth() + 1;
	var tgl = tgl_skrg.getDate();
	var thn = tgl_skrg.getFullYear();

	if (parseInt(eval(splt_tgl[2])) == (thn - 5)) {
		if (parseInt(eval(splt_tgl[1])) == bln) {
			if (parseInt(eval(splt_tgl[0])) > tgl) {
				$('#div_pos_yd' + idx_pos).show();
				$('#div_pos_yd' + idx_pos).html("Ikut Program Posyandu :<br><input type='radio' id='yd" + idx_pos + "' name='indv[" + idx_pos + "][yd]' value='1' >Ya <input type='radio' id='yd" + idx_pos + "' name='indv[" + idx_pos + "][yd]' value='0'>Tidak");
			} else
				$('#div_pos_yd' + idx_pos).html("");
		} else if (parseInt(eval(splt_tgl[1])) > bln) {
			$('#div_pos_yd' + idx_pos).show();
			$('#div_pos_yd' + idx_pos).html("Ikut Program Posyandu :<br><input type='radio' id='yd" + idx_pos + "' name='indv[" + idx_pos + "][yd]' value='1' >Ya <input type='radio' id='yd" + idx_pos + "' name='indv[" + idx_pos + "][yd]' value='0'>Tidak");
		} else
			$('#div_pos_yd' + idx_pos).html("");
	} else if (parseInt(eval(splt_tgl[2])) > (thn - 5)) {
		$('#div_pos_yd' + idx_pos).show();
		$('#div_pos_yd' + idx_pos).html("Ikut Program Posyandu :<br><input type='radio' id='yd" + idx_pos + "' name='indv[" + idx_pos + "][yd]' value='1' >Ya <input type='radio' id='yd" + idx_pos + "' name='indv[" + idx_pos + "][yd]' value='0'>Tidak");
	} else
		$('#div_pos_yd' + idx_pos).html("");

}