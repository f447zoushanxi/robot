
# 是否找到人员
bool found
# 人员中心在 base_link 坐标系下的位置
geometry_msgs/Point position
# 置信度 [0,1]
float32 confidence
# 身份识别结果：owner/guest/unknown
string identity
# 额外调试信息
string message
