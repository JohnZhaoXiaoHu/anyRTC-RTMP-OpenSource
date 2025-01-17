/*
*  Copyright (c) 2021 The AnyRTC project authors. All Rights Reserved.
*
*  Please visit https://www.anyrtc.io for detail.
*
* The GNU General Public License is a free, copyleft license for
* software and other kinds of works.
*
* The licenses for most software and other practical works are designed
* to take away your freedom to share and change the works.  By contrast,
* the GNU General Public License is intended to guarantee your freedom to
* share and change all versions of a program--to make sure it remains free
* software for all its users.  We, the Free Software Foundation, use the
* GNU General Public License for most of our software; it applies also to
* any other work released this way by its authors.  You can apply it to
* your programs, too.
* See the GNU LICENSE file for more info.
*/
#ifndef __I_AR_LIVE_PUSH_Kit_H__
#define __I_AR_LIVE_PUSH_Kit_H__
#include "ArLiveBase.h"

namespace ar {
namespace live {

class IArLivePushEvent
{
public:
	IArLivePushEvent(void) {};
	virtual ~IArLivePushEvent(void) {};

	virtual void onPushEvent(int nEvent, const ArParams&param, uint32_t nElapse) {
		(void)nEvent;
		(void)param;
		(void)nElapse;
	};
	virtual void onNetStatus(const ArParams& status) {
		(void)status;
	};

	/////////////////////////////////////////////////////////////////////////////////
	//
	//              屏幕分享回调
	//
	/////////////////////////////////////////////////////////////////////////////////
	/**
	 * 当屏幕分享开始时，SDK 会通过此回调通知
	 */
	virtual void onScreenCaptureStarted() {};

	/**
	 * 当屏幕分享暂停时，SDK 会通过此回调通知
	 *
	 * @param reason 原因，0：用户主动暂停；1：屏幕窗口不可见暂停
	 */
	virtual void onScreenCapturePaused(int reason) {};

	/**
	 * 当屏幕分享恢复时，SDK 会通过此回调通知
	 *
	 * @param reason 恢复原因，0：用户主动恢复；1：屏幕窗口恢复可见从而恢复分享
	 */
	virtual void onScreenCaptureResumed(int reason) {};

	/**
	 * 当屏幕分享停止时，SDK 会通过此回调通知
	 *
	 * @param reason 停止原因，0：用户主动停止；1：屏幕窗口关闭导致停止
	 */
	virtual void onScreenCaptureStoped(int reason) {};
};



class IArLivePushKit
{
protected:
	IArLivePushKit(void) {};
	virtual ~IArLivePushKit(void) {};

public:
	/* 设置推流事件回调
	参数：
		pEvent	IArLivePushEvent*	回调推流事件接收对象
	*/
	virtual void setArLivePushEvent(IArLivePushEvent*pEvent) = 0;
	//**************************************************************************\\
	// 推流控制
	/* 开始推流
	参数：
		strPushUrl	char*	推流地址
	返回：
		0：调用成功		<0: 失败
	*/
	virtual int startPush(const char* strPushUrl) = 0;
	/* 停止推流
	返回：
		0：调用成功		<0: 失败
	*/
	virtual int stopPush() = 0;
	
	/* 暂停摄像头或屏幕采集并进入垫片推流状态。
	功能：
		暂时停止摄像头或屏幕采集，并使用 ArLivePushConfig.pauseImg 中指定的图片作为替代图像进行推流，也就是所谓的“垫片”。 
		这项功能常用于App被切到后台运行的场景，尤其是在 iOS 系统中，当 App 切到后台以后，操作系统不会再允许该 App 继续使用摄像头。
		此时就可以通过调用 pausePush() 进入垫片状态。
		对于绝大多数推流服务器而言，如果超过一定时间不推视频数据，服务器会断开当前的推流链接。
	返回：
		0：调用成功		<0: 失败
	*/
	virtual int pausePush() = 0;
	/* 恢复摄像头采集并结束垫片推流状态。
	返回：
		0：调用成功		<0: 失败
	*/
	virtual int resumePush() = 0;
	/* 查询是否正在推流。
	返回：
		true：正在推流，false：未推流。
	*/
	virtual bool isPushing() = 0;
};

}
}

#endif	// __I_AR_LIVE_PUSH_Kit_H__
