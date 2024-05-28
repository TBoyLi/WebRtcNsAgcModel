#include <jni.h>
#include <string>
#include <cstdlib>

#include "modules/audio_processing/legacy_ns/noise_suppression.h"
#include "modules/audio_processing/legacy_ns/noise_suppression_x.h"

#if defined(__cplusplus)
extern "C" {
#endif

/**
 * 创建噪声抑制器实例
 * @param env JNI环境指针
 * @param obj 调用此方法的Java对象
 * @return 创建的噪声抑制器实例的指针
 */
JNIEXPORT jlong JNICALL
Java_com_hank_voice_NoiseSuppressor_nsCreate(JNIEnv *env, jobject obj) {
    return (long) WebRtcNs_Create();
}

/**
 * 初始化噪声抑制器实例
 * @param env JNI环境指针
 * @param obj 调用此方法的Java对象
 * @param nsHandler 噪声抑制器实例的指针
 * @param frequency 采样频率
 * @return 如果成功，返回0，如果处理器为空，返回-3
 */
JNIEXPORT jint JNICALL
Java_com_hank_voice_NoiseSuppressor_nsInit(JNIEnv *env, jobject obj, jlong nsHandler,
                                                       jint frequency) {
    NsHandle *handler = (NsHandle *) nsHandler;
    if (handler == nullptr) {
        return -3;
    }
    return WebRtcNs_Init(handler, frequency);
}

/**
 * 设置噪声抑制器的模式
 * @param env JNI环境指针
 * @param obj 调用此方法的Java对象
 * @param nsHandler 噪声抑制器实例的指针
 * @param mode 噪声抑制模式
 * @return 如果成功，返回0，如果处理器为空，返回-3
 */
JNIEXPORT jint JNICALL
Java_com_hank_voice_NoiseSuppressor_nsSetPolicy(JNIEnv *env, jobject obj,
                                                            jlong nsHandler, jint mode) {
    NsHandle *handle = (NsHandle *) nsHandler;
    if (handle == nullptr) {
        return -3;
    }
    return WebRtcNs_set_policy(handle, mode);
}

/**
 * 使用噪声抑制处理音频数据帧
 * @param env JNI环境指针
 * @param obj 调用此方法的Java对象
 * @param nsHandler 噪声抑制器实例的指针
 * @param spframe 输入的音频数据帧
 * @param num_bands 音频数据的频带数量
 * @param outframe 输出的音频数据帧
 * @return 如果成功，返回0，如果处理器为空，返回-3
 */
JNIEXPORT jint JNICALL
Java_com_hank_voice_NoiseSuppressor_nsProcess(JNIEnv *env,
                                                          jobject obj, jlong nsHandler,
                                                          jfloatArray spframe, jint num_bands,
                                                          jfloatArray outframe) {
    NsHandle *handle = (NsHandle *) nsHandler;
    if (handle == nullptr) {
        return -3;
    }
    jfloat *cspframe = env->GetFloatArrayElements(spframe, nullptr);
    jfloat *coutframe = env->GetFloatArrayElements(outframe, nullptr);
    WebRtcNs_Process(handle, &cspframe, num_bands, &coutframe);
    env->ReleaseFloatArrayElements(spframe, cspframe, 0);
    env->ReleaseFloatArrayElements(outframe, coutframe, 0);
    return 0;
}

/**
 * 释放噪声抑制实例
 * @param env JNI环境指针
 * @param obj 调用此方法的Java对象
 * @param nsHandler 噪声抑制器实例的指针
 * @return 如果成功，返回0，如果处理器为空，返回-3
 */
JNIEXPORT jint JNICALL
Java_com_hank_voice_NoiseSuppressor_nsFree(JNIEnv *env,
                                                       jobject obj, jlong
                                                       nsHandler) {
    NsHandle *handle = (NsHandle *) nsHandler;
    if (handle == nullptr) {
        return -3;
    }
    WebRtcNs_Free(handle);
    return 0;
}

/**
 * 创建一个扩展噪声抑制（Nsx）模块实例
 * @param env JNI环境指针
 * @param obj 调用此方法的Java对象
 * @return 创建的扩展噪声抑制（Nsx）模块实例的指针
 */
JNIEXPORT jlong JNICALL
Java_com_hank_voice_NoiseSuppressor_nsxCreate(JNIEnv *env, jobject obj) {
    return (long) WebRtcNsx_Create();
}

/**
 * 初始化扩展噪声抑制（Nsx）模块实例
 * @param env JNI环境指针
 * @param obj 调用此方法的Java对象
 * @param nsHandler 扩展噪声抑制（Nsx）模块实例的指针
 * @param frequency 采样频率
 * @return 如果成功，返回0，如果处理器为空，返回-3
 */
JNIEXPORT jint JNICALL
Java_com_hank_voice_NoiseSuppressor_nsxInit(JNIEnv *env, jobject obj, jlong nsHandler,
                                                        jint frequency
) {
    NsxHandle *handler = (NsxHandle *) nsHandler;
    if (handler == nullptr) {
        return -3;
    }
    return WebRtcNsx_Init(handler, frequency);
}

/**
 * 为扩展噪声抑制（Nsx）模块实例设置策略
 * @param env JNI环境指针
 * @param obj 调用此方法的Java对象
 * @param nsHandler 扩展噪声抑制（Nsx）模块实例的指针
 * @param mode 噪声抑制模式
 * @return 如果成功，返回0，如果处理器为空，返回-3
 */
JNIEXPORT jint JNICALL
Java_com_hank_voice_NoiseSuppressor_nsxSetPolicy(JNIEnv *env,
                                                             jobject obj, jlong
                                                             nsHandler,
                                                             jint mode
) {
    NsxHandle *handle = (NsxHandle *) nsHandler;
    if (handle == nullptr) {
        return -3;
    }
    return WebRtcNsx_set_policy(handle, mode);
}

/**
 * 使用扩展噪声抑制（Nsx）模块处理音频数据帧
 * @param env JNI环境指针
 * @param obj 调用此方法的Java对象
 * @param nsHandler 扩展噪声抑制（Nsx）模块实例的指针
 * @param speechFrame 输入的音频数据帧
 * @param num_bands 音频数据的频带数量
 * @param outframe 输出的音频数据帧
 * @return 如果成功，返回0，如果处理器为空，返回-3
 */
JNIEXPORT jint JNICALL
Java_com_hank_voice_NoiseSuppressor_nsxProcess(JNIEnv *env,
                                                           jobject obj, jlong
                                                           nsHandler,
                                                           jshortArray speechFrame,
                                                           jint num_bands,
                                                           jshortArray outframe) {
    NsxHandle *handle = (NsxHandle *) nsHandler;
    if (handle == nullptr) {
        return -3;
    }
    jshort *cspeechFrame = env->GetShortArrayElements(speechFrame, nullptr);
    jshort *coutframe = env->GetShortArrayElements(outframe, nullptr);
    WebRtcNsx_Process(handle, &cspeechFrame, num_bands, &coutframe);
    env->ReleaseShortArrayElements(speechFrame, cspeechFrame, 0);
    env->ReleaseShortArrayElements(outframe, coutframe, 0);
    return 0;
}

/**
 * 释放扩展噪声抑制（Nsx）模块实例
 * @param env JNI环境指针
 * @param obj 调用此方法的Java对象
 * @param nsHandler 扩展噪声抑制（Nsx）模块实例的指针
 * @return 如果成功，返回0，如果处理器为空，返回-3
 */
JNIEXPORT jint JNICALL
Java_com_hank_voice_NoiseSuppressor_nsxFree(JNIEnv *env, jobject obj, jlong nsHandler) {
    NsxHandle *handle = (NsxHandle *) nsHandler;
    if (handle == nullptr) {
        return -3;
    }
    WebRtcNsx_Free(handle);
    return 0;
}

#if defined(__cplusplus)
}
#endif