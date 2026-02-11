analysis = "AP_Template_GEN"
paths = {"0_00": analysis+'/Datasets/Files/'}

s_ds_info = { # [DatasetName, Production ID, PROC_XSEC[pb], XSEC_UNC[pb], XSEC_Accuracy]
"DY": [
    ["DY",   '99',  500,   0,   'LO'],
],
}




#----------------------------------------------------------------------------------------
# [DO NOT TOUCH THIS PART]
#----------------------------------------------------------------------------------------
s_ds = {}
for period in paths.keys():

    dti = period[0]
    year = period[-2:]

    for key in s_ds_info.keys():
        s_ds[key+"_"+period] = []
        for ds in s_ds_info[key]:
            list_temp = []
            list_temp.append(ds[0]+"_"+period)
            list_temp.append(ds[1]+year+dti)
            list_temp.append(paths[period]+ds[0]+".txt")
            list_temp.append(ds[2])
            list_temp.append(ds[3])
            s_ds[key+"_"+period].append(list_temp)