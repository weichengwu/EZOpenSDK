//
//  EZOpenSDK.h
//  EzvizOpenSDK
//
//  Created by DeJohn Dong on 15/9/10.
//  Copyright (c) 2015年 Ezviz. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "EZConstants.h"

@class EZPlayer;
@class EZDeviceInfo;
@class EZAccessToken;
@class EZCameraInfo;
@class EZDeviceVersion;
@class EZUserInfo;
@class EZProbeDeviceInfo;
@class EZDeviceUpgradeStatus;
@class EZLeaveMessage;

/// 此类为EZOpenSDK接口类 特别说明：110001（参数错误）、110002（AccessToken过期）、149999、150000（服务端异常）是所有http接口（返回值是NSOperation对象的大部分是http接口）都会返回的通用错误码，400002为接口参数错误的通用错误码
@interface EZOpenSDK : NSObject

/**
 *  @since 3.0.0
 *  实例EZOpenSDK接口
 *
 *  @param appKey 传入申请的appKey
 *
 *  @return YES/NO
 */
+ (BOOL)initLibWithAppKey:(NSString *)appKey;

/**
 *  初始化接口，可设置服务器，海外用户使用该初始化方法
 *
 *  @param appKey 传入申请的appKey
 *  @param url apiUrl地址
 *  @param authUrl auth地址
 *
 *  @return YES/NO
 */
+ (BOOL)initLibWithAppKey:(NSString *)appKey
                      url:(NSString *)apiUrl
                  authUrl:(NSString *)authUrl;

/**
 *  @since 3.0.0
 *  销毁EZOpenSDK接口
 *
 *  @return YES/NO
 */
+ (BOOL)destoryLib;

/**
 *  @since 3.0.0
 *  获取SDK版本号接口
 *
 *  @return 版本号
 */
+ (NSString *)getVersion;

/**
 *  @since 3.0.0
 *  打开授权登录中间页面接口
 *
 *  @param block 回调block
 */
+ (void)openLoginPage:(void (^)(EZAccessToken *accessToken))block;

/**
 *  @since 3.0.0
 *  授权登录以后给EZOpenSDK设置accessToken接口
 *
 *  @param accessToken 授权登录获取的accessToken
 */
+ (void)setAccessToken:(NSString *)accessToken;

/**
 *  @since 3.0.0
 *  账户注销接口
 *
 *  @param completion 回调block，error为空表示登出成功
 */
+ (void)logout:(void (^)(NSError *error))completion;

/**
 *  @since 3.0.0
 *  根据alarmId删除告警信息接口
 *
 *  @param alarmIds   告警信息Id数组(可以只有一个Id)，最多为10个Id，否则会报错
 *  @param completion 回调block，error为空时表示删除成功
 *
 *  @return operation
 */
+ (NSURLSessionDataTask *)deleteAlarm:(NSArray *)alarmIds
                  completion:(void (^)(NSError *error))completion;

/**
 *  @since 3.0.0
 *  设置告警信息为已读接口
 *
 *  @param alarmIds   告警信息Id数组(可以只有一个Id)，最多为10个id,否则会报错
 *  @param status     告警消息状态
 *  @param completion 回调block，error为空时表示设置成功
 *
 *  @return operation
 */
+ (NSURLSessionDataTask *)setAlarmStatus:(NSArray *)alarmIds
                    alarmStatus:(EZMessageStatus)status
                     completion:(void (^)(NSError *error))completion;


/**
 *  @since 3.0.0
 *  根据设备序列号删除当前账号的设备接口
 *
 *  @param deviceSerial 设备序列号
 *  @param completion   回调block，error为空时表示删除成功
 *  @see 该接口与终端绑定功能相关，会遇到删除时报106002的错误，请关闭终端绑定以后再试
 *
 *  @return operation
 */
+ (NSURLSessionDataTask *)deleteDevice:(NSString *)deviceSerial
                   completion:(void (^)(NSError *error))completion;

/**
 *  @since 3.0.0
 *  WiFi配置开始接口
 *
 *  @param ssid         连接WiFi SSID
 *  @param password     连接WiFi 密码
 *  @param deviceSerial 连接WiFi的设备的设备序列号
 *  @param statusBlock  返回连接设备的WiFi配置状态
 *
 *  @return YES/NO
 */
+ (BOOL)startConfigWifi:(NSString *)ssid
               password:(NSString *)password
           deviceSerial:(NSString *)deviceSerial
           deviceStatus:(void (^)(EZWifiConfigStatus status))statusBlock;

/**
 *  @since 3.0.0
 *  Wifi配置停止接口
 *
 *  @return YES/NO
 */
+ (BOOL)stopConfigWifi;

/**
 *  @since 3.0.0
 *  PTZ 控制接口
 *
 *  @param deviceSerial 设备序列号
 *  @param cameraNo     通道号
 *  @param command      ptz控制命令
 *  @param action       控制启动/停止
 *  @param speed        云台速度：0-慢，1-适中，2-快
 *  @param resultBlock  回调block，当error为空时表示操作成功
 *
 *  @return operation
 */
+ (NSURLSessionDataTask *)controlPTZ:(NSString *)deviceSerial
                   cameraNo:(NSInteger)cameraNo
                    command:(EZPTZCommand)command
                     action:(EZPTZAction)action
                      speed:(NSInteger)speed
                     result:(void (^)(NSError *error))resultBlock;

/**
 *  @since 3.0.0
 *  摄像头显示控制接口
 *
 *  @param deviceSerial 设备序列号
 *  @param cameraNo     通道号
 *  @param command      显示控制命令
 *  @param resultBlock  回调block，当error为空时表示操作成功
 */
+ (void)controlVideoFlip:(NSString *)deviceSerial
                cameraNo:(NSInteger)cameraNo
                 command:(EZDisplayCommand)command
                  result:(void (^)(NSError *error))resultBlock;

/**
 *  @since 3.0.0
 *  根据cameraId构造EZPlayer对象
 *
 *  @param deviceSerial 设备序列号
 *  @param cameraNo     通道号
 *
 *  @return EZPlayer对象
 */
+ (EZPlayer *)createPlayerWithDeviceSerial:(NSString *)deviceSerial
                                  cameraNo:(NSInteger)cameraNo;

+ (EZPlayer *)createPlayerWithDeviceSerial:(NSString *)deviceSerial strCameraNo:(NSString *)strCameraNo;

/**
 *  @since 3.0.0
 *  根据url构造EZPlayer对象 （主要用来处理视频广场的播放）
 *
 *  @param url 播放url，目前只支持该协议：ysproto://vtm.ys7.com:8554/live?dev=531993276&chn=1&stream=1&cln=1&isp=0&biz=3
 *
 *  @return EZPlayer对象
 */
+ (EZPlayer *)createPlayerWithUrl:(NSString *)url;


/**
 *  @since 3.0.0
 *  释放EZPlayer对象
 *
 *  @param player EZPlayer对象
 *
 *  @return YES/NO
 */
+ (BOOL)releasePlayer:(EZPlayer *)player;

#pragma mark - V3.1 新增加接口

/**
 *  @since 3.1.0
 *  数据解密
 *
 *  @param data       需要解密的数据
 *  @param verifyCode 设备验证码
 *
 *  @return 解密的NSData对象，如果返回的数据是空的，请检查密码是否正确或者传入的数据是否正确。
 */
+ (NSData *)decryptData:(NSData *)data verifyCode:(NSString *)verifyCode;


#pragma mark - V3.2 新增加接口

/**
 *  @since 3.2.0
 *  获取设备的版本信息接口
 *
 *  @param deviceSerial 设备序列号
 *  @param completion   回调block，正常时返回EZDeviceVersion的对象信息，错误时返回错误码
 *
 *  @return operation
 */
+ (NSURLSessionDataTask *)getDeviceVersion:(NSString *)deviceSerial
                       completion:(void (^)(EZDeviceVersion *version, NSError *error))completion;


/**
 *  @since 4.2.0
 *  通过设备验证码开关视频图片加密接口
 *
 *  @param isEncrypt    是否加密，只有NO(关闭)的时候需要设备验证码的相关参数(vaildateCode)
 *  @param deviceSerial 设备序列号
 *  @param verifyCode 设备验证码
 *  @param completion   回调block，error为空时表示操作成功
 *
 *  @return operation
 */
+ (NSURLSessionDataTask *)setDeviceEncryptStatus:(NSString *)deviceSerial
                             verifyCode:(NSString *)verifyCode
                                encrypt:(BOOL)isEncrypt
                             completion:(void (^)(NSError *error))completion;

/**
 *  @since 3.2.0
 *  根据设备序列号修改设备名称接口
 *
 *  @param deviceSerial 设备序列号
 *  @param deviceName   设备名称
 *  @param completion   回调block，error为空时表示修改成功
 *
 *  @return operation
 */
+ (NSURLSessionDataTask *)setDeviceName:(NSString *)deviceName
                  deviceSerial:(NSString *)deviceSerial
                    completion:(void (^)(NSError *error))completion;

/**
 *  @since 3.2.0
 *  获取用户基本信息的接口
 *
 *  @param completion 回调block， 正常时返回EZUserInfo的对象，错误时返回错误码
 *
 *  @return operation
 */
+ (NSURLSessionDataTask *)getUserInfo:(void (^)(EZUserInfo *userInfo, NSError *error))completion;

/**
 *  @since 3.2.0
 *  根据设备序列号获取未读消息数，设备序列号为空时获取所有设备的未读消息数
 *
 *  @param deviceSerial 需要获取的设备序列号，为空时返回账户下所有设备的未读消息数
 *  @param type         消息类型：EZMessageTypeAlarm 告警消息（1），EZMessageTypeLeave 留言消息（2）
 *  @param completion   回调block，正常时返回未读数量，错误时返回错误码
 *
 *  @return operation
 */
+ (NSURLSessionDataTask *)getUnreadMessageCount:(NSString *)deviceSerial
                           messageType:(EZMessageType)type
                            completion:(void (^)(NSInteger count, NSError *error))completion;

/**
 *  @since 3.2.0
 *  根据设备序列号获取设备的留言消息列表
 *
 *  @param deviceSerial 需要获取的设备序列号
 *  @param beginTime    开始时间
 *  @param endTime      结束时间
 *  @param pageIndex    分页页码
 *  @param pageSize     分页单页数量
 *  @param completion   回调block，正常时返回EZLeaveMessage的对象数组，错误时返回错误码
 *
 *  @return operation
 */
+ (NSURLSessionDataTask *)getLeaveMessageList:(NSString *)deviceSerial
                           pageIndex:(NSInteger)pageIndex
                            pageSize:(NSInteger)pageSize
                           beginTime:(NSDate *)beginTime
                             endTime:(NSDate *)endTime
                          completion:(void (^)(NSArray *leaveMessageList, NSInteger totalCount, NSError *error))completion;

/**
 *  @since 3.2.0
 *  根据leaveId设置留言消息状态
 *
 *  @param leaveIds   留言消息Id数组(最大数量为10，允许只有1个)
 *  @param status     需要设置的留言状态，目前只支持 EZMessageStatusRead(已读)
 *  @param completion 回调block，error为空表示设置成功
 *
 *  @return operation
 */
+ (NSURLSessionDataTask *)setLeaveMessageStatus:(NSArray *)leaveIds
                         messageStatus:(EZMessageStatus)status
                            completion:(void (^)(NSError *error))completion;

/**
 *  @since 3.2.0
 *  根据leaveId删除留言消息
 *
 *  @param leaveIds   留言消息Id数组(最大数量为10，允许只有1个)
 *  @param completion 回调block，error为空表示删除成功
 *
 *  @return operation
 */
+ (NSURLSessionDataTask *)deleteLeaveMessage:(NSArray *)leaveIds
                         completion:(void (^)(NSError *error))completion;

/**
 *  @since 3.2.0
 *  根据设备序列号获取存储介质状态(如是否初始化，格式化进度等)
 *
 *  @param deviceSerial 设备序列号
 *  @param completion   回调block，正常时返回EZStorageInfo的对象数组，错误时返回错误码
 *
 *  @return operation
 */
+ (NSURLSessionDataTask *)getStorageStatus:(NSString *)deviceSerial
                       completion:(void (^)(NSArray *storageStatus, NSError *error))completion;

/**
 *  @since 3.2.0
 *  根据设备序列号和分区编号格式化分区（SD卡）
 *
 *  @param deviceSerial 设备序列号
 *  @param storageIndex 查询返回的分区号，0表示全部格式化，可能会有几块硬盘的情况
 *  @param completion   回调block，error为空表示设置成功
 *
 *  @return operation
 */
+ (NSURLSessionDataTask *)formatStorage:(NSString *)deviceSerial
                  storageIndex:(NSInteger)storageIndex
                    completion:(void (^)(NSError *error))completion;
/**
 *  @since 3.2.0
 *  尝试查询设备信息，设备Wifi配置前查询一次设备的信息
 *
 *  @param deviceSerial 设备序列号
 *  @param deviceType 设备型号，无法获取到设备型号则可传nil
 *  @param completion   回调block，正常时返回EZProbeDeviceInfo对象，错误码返回错误码
 *  @see 全新的设备是没有注册到平台的，所以会出现设备不存在的情况，设备wifi配置成功以后会上报数据到萤石云平台，以后每次查询就不会出现设备不存在的情况了。
 *
 *  @return operation
 */
+ (NSURLSessionDataTask *)probeDeviceInfo:(NSString *) deviceSerial
                      deviceType:(NSString *) deviceType
                      completion:(void (^)(EZProbeDeviceInfo *deviceInfo, NSError *error))completion;

/**
 *  @since 3.2.0
 *  根据设备序列号获取设备升级时的进度状态
 *
 *  @param deviceSerial 设备序列号
 *  @param completion   回调block，正常时返回EZDeviceUpgradeStatus对象，错误时返回错误码
 *
 *  @return operation
 */
+ (NSURLSessionDataTask *)getDeviceUpgradeStatus:(NSString *)deviceSerial
                             completion:(void (^)(EZDeviceUpgradeStatus *status, NSError *error))completion;

/**
 *  @since 3.2.0
 *  通过设备序列号对设备进行升级操作，前提是该设备有更新软件的提示
 *
 *  @param deviceSerial 设备序列号
 *  @param completion   回调block，error为空表示操作成功
 *
 *  @return operation
 */
+ (NSURLSessionDataTask *)upgradeDevice:(NSString *)deviceSerial
                    completion:(void (^)(NSError *error))completion;


/**
 *  @since 3.2.0
 *  根据EZLeaveMessage对象信息获取语音留言消息数据接口
 *  @param message    留言消息对象
 *  @param completion 回调block （resultCode = 1 表示语音下载成功，-1表示下载失败）
 *
 *  @return operation
 */
+ (NSOperation *)getLeaveMessageData:(EZLeaveMessage *)message
                          completion:(void (^)(NSData *data, NSInteger resultCode))completion;

/**
 *  @since 1.0.0
 *  打开云存储中间页
 *
 *  @param deviceSerial 设备序列号
 *  @param channelNo    设备通道号
 */
+ (void)openCloudPage:(NSString *)deviceSerial channelNo:(NSInteger)channelNo;

#pragma mark - V3.3 新增加接口

/**
 *  @since 3.3.0
 *  打开修改密码中间页
 *
 *  @param completion 回调block resultCode为0时表示修改密码成功
 */
+ (void)openChangePasswordPage:(void (^)(NSInteger resultCode))completion;

#pragma mark - V4.0 新增加接口

/**
 *  @since 4.0.0
 *  设置p2p功能是否开启接口，默认不开启p2p，用户自己选择是否开启
 *
 *  @param enable p2p是否开启
 */
+ (void)enableP2P:(BOOL)enable;

/**
 *  @since 4.0.0
 *  设置是否打印debug日志,需在初始化sdk之前调用
 *
 *  @param enable 是否打印日志，默认关闭
 *
 *  @return YES/NO
 */
+ (BOOL)setDebugLogEnable:(BOOL)enable;

#pragma mark - V4.2 新增加接口

/**
 *  @since 4.2.0
 *  获取用户所有的设备列表
 *
 *  @param pageIndex  分页当前页码（从0开始）
 *  @param pageSize   分页每页数量（建议20以内）
 *  @param completion 回调block，正常时返回EZDeviceInfo的对象数组和设备总数，错误时返回错误码
 *
 *  @return operation
 */
+ (NSURLSessionDataTask *)getDeviceList:(NSInteger)pageIndex
                               pageSize:(NSInteger)pageSize
                             completion:(void (^)(NSArray *deviceList, NSInteger totalCount, NSError *error))completion;

/**
 *  @since 4.2.0
 *  获取分享给用户的设备列表接口
 *
 *  @param pageIndex  分页当前页码（从0开始）
 *  @param pageSize   分页每页数量（建议20以内）
 *  @param completion 回调block，正常时返回EZDeviceInfo的对象数组和设备总数，错误时返回错误码
 *
 *  @return operation
 */
+ (NSURLSessionDataTask *)getSharedDeviceList:(NSInteger)pageIndex
                                     pageSize:(NSInteger)pageSize
                                   completion:(void (^)(NSArray *deviceList, NSInteger totalCount, NSError *error))completion;

/**
 *  @since 4.2.0
 *  查询云存储录像信息列表接口
 *
 *  @param deviceSerial 设备序列号
 *  @param cameraNo     通道号
 *  @param beginTime    查询时间范围开始时间
 *  @param endTime      查询时间范围结束时间
 *  @param completion   回调block，正常时返回EZCloudRecordFile的对象数组，错误时返回错误码
 *
 *  @return operation
 */
+ (NSURLSessionDataTask *)searchRecordFileFromCloud:(NSString *)deviceSerial
                                           cameraNo:(NSInteger)cameraNo
                                          beginTime:(NSDate *)beginTime
                                            endTime:(NSDate *)endTime
                                         completion:(void (^)(NSArray *couldRecords, NSError *error))completion;

/**
 *  @since 4.2.0
 *  查询远程SD卡存储录像信息列表接口
 *
 *  @param deviceSerial 设备序列号
 *  @param cameraNo     通道号
 *  @param beginTime    查询时间范围开始时间
 *  @param endTime      查询时间范围结束时间
 *  @param completion   回调block，正常时返回EZDeviceRecordFile的对象数组，错误时返回错误码
 *
 *  @return operation
 */
+ (NSURLSessionDataTask *)searchRecordFileFromDevice:(NSString *)deviceSerial
                                            cameraNo:(NSInteger)cameraNo
                                           beginTime:(NSDate *)beginTime
                                             endTime:(NSDate *)endTime
                                          completion:(void (^)(NSArray *deviceRecords, NSError *error))completion;

/**
 *  @since 4.2.0
 *  根据设备序列号获取告警信息列表，设备序列号为nil时查询整个账户下的告警信息列表
 *
 *  @param deviceSerial 设备序列号
 *  @param pageIndex    分页当前页码（从0开始）
 *  @param pageSize     分页每页数量（建议20以内）
 *  @param beginTime    搜索时间范围开始时间
 *  @param endTime      搜索时间范围结束时间
 *  @param completion   回调block，正常时返回EZAlarmInfo的对象数据和查询时间范围内的告警个数的总数，错误时返回错误码
 *
 *  @return operation
 */
+ (NSURLSessionDataTask *)getAlarmList:(NSString *)deviceSerial
                             pageIndex:(NSInteger)pageIndex
                              pageSize:(NSInteger)pageSize
                             beginTime:(NSDate *)beginTime
                               endTime:(NSDate *)endTime
                            completion:(void (^)(NSArray *alarmList, NSInteger totalCount, NSError *error))completion;

/**
 *  @since 4.2.0
 *  根据设备序列号和设备验证码添加设备接口
 *
 *  @param deviceSerial 设备序列号
 *  @param verifyCode   设备验证码
 *  @param completion   回调block，error为空时表示添加成功
 *
 *  @return operation
 */
+ (NSURLSessionDataTask *)addDevice:(NSString *)deviceSerial
                verifyCode:(NSString *)verifyCode
                completion:(void (^)(NSError *error))completion;

/**
 *  @since 4.2.0
 *  获取抓取摄像头图片的url接口
 *
 *  @param deviceSerial 设备序列号
 *  @param cameraNo     通道号
 *  @param completion   回调block，正常时返回url地址信息，错误时返回错误码
 *  @see 该接口比较耗时，不建议进行批量设备抓图，SDK内部只支持6个http请求并发，该接口会持续占用http请求资源，如果遇到http请求延时巨大问题，优先考虑抓图接口并发造成的问题,
 *  抓图将在服务器端保留2个小时
 *
 *  @return operation
 */
+ (NSURLSessionDataTask *)captureCamera:(NSString *)deviceSerial
                      cameraNo:(NSInteger)cameraNo
                    completion:(void (^)(NSString *url, NSError *error))completion;

/**
 *  @since 4.2.0
 *  设置设备通道的清晰度
 *
 *  @param deviceSerial 设备序列号
 *  @param cameraNo     通道号
 *  @param videoLevel   通道清晰度，0-流畅，1-均衡，2-高清，3-超清
 *  @param completion   回调block，无error表示设置成功
 *  @see 如果是正在播放时调用该接口，设置清晰度成功以后必须让EZPlayer调用stopRealPlay再调用startRealPlay重新取流才成完成画面清晰度的切换。
 *
 *  @return operation
 */
+ (NSURLSessionDataTask *)setVideoLevel:(NSString *)deviceSerial
                      cameraNo:(NSInteger)cameraNo
                    videoLevel:(EZVideoLevelType)videoLevel
                    completion:(void (^)(NSError *error))completion;


/**
 *  @since 4.2.0
 *  设备设置布防状态，兼容A1和IPC设备的布防
 *
 *  @param defence      布防状态, IPC布防状态只有0和1，A1有0:睡眠 8:在家 16:外出
 *  @param deviceSerial 设备序列号
 *  @param completion   回调block，error为空表示设置成功
 *
 *  @return operation
 */
+ (NSURLSessionDataTask *)setDefence:(EZDefenceStatus)defence
               deviceSerial:(NSString *)deviceSerial
                 completion:(void (^)(NSError *error))completion;

#pragma mark - V4.3 新增加接口

/**
 *  @since 4.3.0
 *  根据序列号获取设备信息
 *
 *  @param deviceSerial 设备序列号
 *  @param completion 回调block，正常时返回EZDeviceInfo的对象，错误时返回错误码
 *
 *  @return operation
 */
+ (NSURLSessionDataTask *)getDeviceInfo:(NSString *)deviceSerial
                    completion:(void (^)(EZDeviceInfo *deviceInfo, NSError *error))completion;

/**
 *  @since 4.3.0
 *  获取终端（手机等）唯一识别码
 *
 *  @return 终端唯一识别码
 */
+ (NSString *) getTerminalId;

#pragma mark - V4.4 新增加接口

/**
 *  @since 4.4.0
 *  push初始化接口，不需要push服务则无需调用
 */
+ (void) initPushService;

#pragma mark - V4.5 新增加接口

/**
 清除取流时的缓存数据
 */
+ (void) clearStreamInfoCache;

#pragma mark - V4.8.2 新增加接口

/**
 是否已经登录

 @return YES：已经登录；NO：未登录
 */
+ (BOOL) isLogin;

/**
 获取当前accessToken

 @return accessToken
 */
+ (NSString *) getAccesstoken;

/**
 根据应用类型判断是否安装了对应的应用
 
 @param appType 应用类型
 @return YES:已安装，NO:没有安装或安装的萤石APP版本过低
 */
+ (BOOL) isEzvizAppInstalledWithType:(EZAppType) appType;


/**
 跳转到指定萤石APP进行授权登录

 @param appType 萤石APP类型
 @return 跳转结果
 */
+ (BOOL) ezvizLoginWithAppType:(EZAppType) appType;

/**
 跳转到指定APP的指定界面
 
 @param pageType 界面类型
 @param appType APP类型
 @return 跳转结果
 */
+ (BOOL) gotoEzvizAppPage:(EZAppPageType) pageType appType:(EZAppType) appType;

/**
 外部跳转处理方法，适用于iOS9以上，包括iOS9

 @param url 跳转过来的url
 @param opetions 参数，默认为空，目前未进行处理，预留
 @param delegate 委托
 @return 结果
 */
+ (BOOL) handleOpenUrl:(NSURL *) url options:(NSDictionary *) opetions delegate:(id<EZOpenSDKDelegate>) delegate;

/**
 外部跳转处理方法，适用于iOS8以下,包括iOS8

 @param url 跳转过来的url
 @param delegate 委托
 @return 结果
 */
+ (BOOL) handleOpenUrl:(NSURL *) url delegate:(id<EZOpenSDKDelegate>) delegate;

/**
 外部跳转处理方法，适用于iOS8以下,包括iOS8

 @param url 跳转过来的url
 @param sourceApplication 源APP
 @param annotation 注释
 @param delegate 委托
 @return 结果
 */
+ (BOOL) handleOpenUrl:(NSURL *) url
     sourceApplication:(NSString *) sourceApplication
            annotation:(id) annotation
              delegate:(id<EZOpenSDKDelegate>) delegate;

#pragma mark - V4.8.3 新增加接口

/**
 *  @since 4.8.3
 *  WiFi配置开始接口
 *
 *  @param ssid         连接WiFi SSID
 *  @param password     连接WiFi 密码
 *  @param deviceSerial 连接WiFi的设备的设备序列号,批量配置时填nil
 *  @param mode         配网的方式，EZWiFiConfigMode中列举的模式进行任意组合,例如:EZWiFiConfigSmart|EZWiFiConfigWave
 *  @param statusBlock  返回设备序列号以及当前连接状态
 *
 *  @return YES/NO
 */
+ (BOOL)startConfigWifi:(NSString *) ssid
               password:(NSString *) password
           deviceSerial:(NSString *) deviceSerial
                   mode:(NSInteger) mode
           deviceStatus:(void (^)(EZWifiConfigStatus status,NSString *deviceSerial))statusBlock;
    
#pragma mark - V4.8.4
/**
 AP配网接口
 
 @param ssid WiFi的ssid
 @param password WiFi的密码
 @param deviceSerial 设备序列号
 @param verifyCode 设备验证码
 @param callback 结果回调
 @return 成功或失败
 */
+ (BOOL)startAPConfigWifiWithSsid:(NSString *) ssid
                         password:(NSString *) password
                     deviceSerial:(NSString *) deviceSerial
                       verifyCode:(NSString *) verifyCode
                           result:(void (^)(BOOL ret)) callback;
    
/**
 停止AP配网
 */
+ (void)stopAPConfigWifi;


#pragma mark - v4.10

/// 获取手表服务相关信息
/// @param deviceId 设备序列号
/// @param completion operation
+ (void)requestGetWatchServerInfo:(NSString *)deviceId
                       completion:(void (^)(id watchServerInfo, NSError *error))completion;


/// 是否支持国标
/// @param enable YES or NO
+ (void)enableNationalStandard:(BOOL)enable;


#pragma mark - v4.11

/**
*  @since 4.11.0
*  设置debug日志回调,需在初始化sdk之前调用
*
*  @param logCallback 日志回调
*/
+ (void)setDebugLogCallBack:(void(^)(NSString *logStr))logCallback;


#pragma mark - v4.13
/**
 *  获取指定时间内的所有录像文件
 *
 *  @param deviceSerial 设备序列号
 *  @param cameraNo     通道号，传入<=0的值则为默认值
 *  @param beginTime    开始时间，传入nil则为当天00:00:00
 *  @param endTime      结束时间，传入nil则为当天23:59:59
 *  @param rectype      回放源，0-系统自动选择，1-云存储，2-本地录像。非必选，默认为0，传入负值则为默认值
 *  @param bizType       设备归属业务来源
 *  @param platFormId  平台ID
 *  @param completion   回调block records:EzvizRecordFileInfo的数组
 *
 *  @return operation
 */
+ (NSURLSessionDataTask *)searchRecordFile:(NSString *) deviceSerial
                                  cameraNo:(NSString *) cameraNo
                                 beginTime:(NSDate *) beginTime
                                   endTime:(NSDate *) endTime
                                   recType:(NSInteger) rectype
                                   bizType:(NSString *)bizType
                                platFormId:(NSString *)platFormId
                                completion:(void (^)(id records, NSError *error))completion;

@end
