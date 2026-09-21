import json

try:
    with open('/home/joraxorosh/school21/python_backend/AP1_Py_T01.ID_1375362-1/src/task6/input.txt', 'r') as f:
        data = json.load(f)
    list1 = data['list1']
    list2 = data['list2']
    merged_list = list1 + list2
    for i in range(len(merged_list)):
        for j in range(i+1, len(merged_list)):
            if merged_list[j]["year"] < merged_list[i]["year"]:
                temp = merged_list[i]
                merged_list[i] = merged_list[j]
                merged_list[j] = temp
    print(json.dumps(merged_list, indent=2, ensure_ascii=False))
except:
    print("Некорректный ввод!")