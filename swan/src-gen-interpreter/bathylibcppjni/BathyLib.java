/* DO NOT EDIT THIS FILE - it is machine generated */

/**
 * Design Pattern inspired from https://dhilst.github.io/2016/10/15/JNI-CPP.html
 * Principle: a java long attribute to keep the link to the C++ object
 */
package bathylibcppjni;

public class BathyLib
{
	private final static String N_WS_PATH = "/cea/dsku/u-pong/temp1/b4/lemairen/Workspace/swan";

	static
	{
		System.load(N_WS_PATH + "/swan/src-gen-interpreter/bathylibcppjni/lib/libbathylibcppjni.so");
	}

	private long nativeObjectPointer;

	private native long nativeNew();
	private native void nativeDelete(final long nativeObjectPointer);

	public BathyLib()
	{
		nativeObjectPointer = nativeNew();	
	}

	@Override
	public void finalize()
	{
		nativeDelete(nativeObjectPointer);
	}

	public native void jsonInit(String jsonContent);
	public native double nextDepth();
	public native double nextWaveHeight();
}
