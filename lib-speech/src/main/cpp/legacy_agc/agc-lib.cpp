#include <jni.h>
#include <string>
#include <cstdlib>

#include "modules/audio_processing/agc/legacy/gain_control.h"

#if defined(__cplusplus)
extern "C" {
#endif

/**
 * 创建一个自动增益控制实例 返回一个长整型，代表创建的实例的指针
 * @param env JNI环境指针
 * @param obj 调用此方法的Java对象
 * @return 创建的自动增益控制实例的指针
 */
JNIEXPORT jlong JNICALL
Java_com_hank_voice_AutomaticGainControl_agcCreate(JNIEnv *env, jobject obj) {
    return (long) WebRtcAgc_Create();
}

/**
 * 释放一个自动增益控制实例 如果成功，返回0，如果处理器为空，返回-3
 * @param env JNI环境指针
 * @param obj 调用此方法的Java对象
 * @param agcInst 自动增益控制实例的指针
 * @return 如果成功，返回0，如果处理器为空，返回-3
 */
JNIEXPORT jint JNICALL
Java_com_hank_voice_AutomaticGainControl_agcFree(JNIEnv *env, jobject obj,
                                                             jlong agcInst) {
    void *_agcInst = (void *) agcInst;
    if (_agcInst == nullptr)
        return -3;
    WebRtcAgc_Free(_agcInst);
    return 0;
}

/**
 * 初始化自动增益控制实例 如果成功，返回0，如果处理器为空，返回-3
 * @param env JNI环境指针
 * @param obj 调用此方法的Java对象
 * @param agcInst 自动增益控制实例的指针
 * @param minLevel 最小增益级别
 * @param maxLevel 最大增益级别
 * @param agcMode 自动增益控制模式
 * @param fs 采样率
 * @return 如果成功，返回0，如果处理器为空，返回-3
 */
JNIEXPORT jint JNICALL
Java_com_hank_voice_AutomaticGainControl_agcInit(JNIEnv *env,
                                                             jobject obj, jlong agcInst,
                                                             jint minLevel, jint maxLevel,
                                                             jint agcMode, jint fs) {
    void *_agcInst = (void *) agcInst;
    if (_agcInst == nullptr)
        return -3;
    return WebRtcAgc_Init(_agcInst, minLevel, maxLevel, agcMode, fs);
}

/**
 * 设置自动增益控制实例的配置 如果成功，返回0，如果处理器为空，返回-3
 * @param env JNI环境指针
 * @param obj 调用此方法的Java对象
 * @param agcInst 自动增益控制实例的指针
 * @param targetLevelDbfs 目标音量级别（单位：dBFS）
 * @param compressionGaindB 压缩增益（单位：dB）
 * @param limiterEnable 是否启用限制器
 * @return 如果成功，返回0，如果处理器为空，返回-3
 */
JNIEXPORT jint JNICALL
Java_com_hank_voice_AutomaticGainControl_agcSetConfig(JNIEnv *env, jobject obj,
                                                                  jlong agcInst,
                                                                  jshort targetLevelDbfs,
                                                                  jshort compressionGaindB,
                                                                  jboolean limiterEnable
) {
    void *_agcInst = (void *) agcInst;
    if (_agcInst == nullptr)
        return -3;
    WebRtcAgcConfig setConfig;
    setConfig.targetLevelDbfs = targetLevelDbfs;
    setConfig.compressionGaindB = compressionGaindB;
    setConfig.limiterEnable = limiterEnable;
    return WebRtcAgc_set_config(_agcInst, setConfig);
}

/**
 * 分析音频数据帧，计算增益值 如果成功，返回0，如果处理器为空，返回-3
 * @param env JNI环境指针
 * @param obj 调用此方法的Java对象
 * @param agcInst 自动增益控制实例的指针
 * @param inNear 近端音频数据
 * @param num_bands 音频数据的频带数量
 * @param samples 音频数据的样本数量
 * @param out 输出音频数据
 * @param inMicLevel 输入麦克风级别
 * @param outMicLevel 输出麦克风级别
 * @param echo 回声消除
 * @param saturationWarning 饱和警告
 * @return 如果成功，返回0，如果处理器为空，返回-3
 */
JNIEXPORT jint JNICALL
Java_com_hank_voice_AutomaticGainControl_agcProcess(JNIEnv *env, jobject obj,
                                                                jlong agcInst,
                                                                jshortArray inNear,
                                                                jint num_bands,
                                                                jint samples, jshortArray out,
                                                                jint inMicLevel,
                                                                jint outMicLevel,
                                                                jint echo,
                                                                jboolean saturationWarning) {
    void *_agcInst = (void *) agcInst;
    if (_agcInst == nullptr)
        return -3;
    jshort *cinNear = env->GetShortArrayElements(inNear, nullptr);
    jshort *cout = env->GetShortArrayElements(out, nullptr);

    int32_t gains[11] = {};
    jint ret = WebRtcAgc_Analyze(_agcInst, &cinNear, num_bands, samples, inMicLevel, &outMicLevel,
                                 echo, &saturationWarning, gains);
    if (ret == 0)
        ret = WebRtcAgc_Process(_agcInst, gains, &cinNear, num_bands, &cout);
    env->ReleaseShortArrayElements(inNear, cinNear, 0);
    env->ReleaseShortArrayElements(out, cout, 0);
    return ret;
}

/**
 * 添加远端音频数据帧，用于计算增益值 如果成功，返回0，如果处理器为空，返回-3
 * @param env JNI环境指针
 * @param obj 调用此方法的Java对象
 * @param agcInst 自动增益控制实例的指针
 * @param inFar 远端音频数据
 * @param samples 音频数据的样本数量
 * @return 如果成功，返回0，如果处理器为空，返回-3
 */
JNIEXPORT jint JNICALL
Java_com_hank_voice_AutomaticGainControl_agcAddFarend(JNIEnv *env, jobject obj,
                                                                  jlong agcInst,
                                                                  jshortArray inFar,
                                                                  jint samples) {
    void *_agcInst = (void *) agcInst;
    if (_agcInst == nullptr)
        return -3;
    short *cinFar = env->GetShortArrayElements(inFar, nullptr);
    jint ret = WebRtcAgc_AddFarend(_agcInst, cinFar, samples);
    env->ReleaseShortArrayElements(inFar, cinFar, 0);
    return ret;
}

/**
 * 添加麦克风音频数据帧，用于计算增益值 如果成功，返回0，如果处理器为空，返回-3
 * @param env JNI环境指针
 * @param obj 调用此方法的Java对象
 * @param agcInst 自动增益控制实例的指针
 * @param inMic 麦克风音频数据
 * @param num_bands 音频数据的频带数量
 * @param samples 音频数据的样本数量
 * @return 如果成功，返回0，如果处理器为空，返回-3
 */
JNIEXPORT jint JNICALL
Java_com_hank_voice_AutomaticGainControl_agcAddMic(JNIEnv *env, jobject obj,
                                                               jlong agcInst,
                                                               jshortArray inMic,
                                                               jint num_bands, jint samples
) {
    void *_agcInst = (void *) agcInst;
    if (_agcInst == nullptr)
        return -3;
    short *cinMic = env->GetShortArrayElements(inMic, nullptr);
    jint ret = WebRtcAgc_AddMic(_agcInst, &cinMic, num_bands, samples);
    env->ReleaseShortArrayElements(inMic, cinMic, 0);
    return ret;
}

/**
 * 使用虚拟麦克风音频数据帧，用于计算增益值 如果成功，返回0，如果处理器为空，返回-3
 * @param env JNI环境指针
 * @param obj 调用此方法的Java对象
 * @param agcInst 自动增益控制实例的指针
 * @param inMic 麦克风音频数据
 * @param num_bands 音频数据的频带数量
 * @param samples 音频数据的样本数量
 * @param micLevelIn 输入麦克风级别
 * @param micLevelOut 输出麦克风级别
 * @return 如果成功，返回0，如果处理器为空，返回-3
 */
JNIEXPORT jint JNICALL
Java_com_hank_voice_AutomaticGainControl_agcVirtualMic(JNIEnv *env, jobject obj,
                                                                   jlong agcInst,
                                                                   jshortArray inMic,
                                                                   jint num_bands,
                                                                   jint samples,
                                                                   jint micLevelIn,
                                                                   jint micLevelOut
) {
    void *_agcInst = (void *) agcInst;
    if (_agcInst == nullptr)
        return -3;
    jshort *cinMic = env->GetShortArrayElements(inMic, nullptr);
    jint ret = WebRtcAgc_VirtualMic(_agcInst, &cinMic, num_bands, samples, micLevelIn,
                                    &micLevelOut);
    env->ReleaseShortArrayElements(inMic, cinMic, 0);
    return ret;
}

#if defined(__cplusplus)
}
#endif