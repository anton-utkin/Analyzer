package com.utkin.analyzerapp

import android.os.AsyncTask;
import android.os.Environment;
import android.util.Log;

import java.io.BufferedInputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.URL;
import java.net.URLConnection;
import java.nio.charset.Charset;
import java.util.Scanner;

class AnalyzerAsyncTask : AsyncTask<String, String, String> {
    private val TAG = AnalyzerAsyncTask::class.simpleName;

    companion object {
        val SUCCESS = "SUCCESS";
        val PROCESSING = "PROCESSING";
        private val DATA_FILE_NAME = Environment.getExternalStorageDirectory().toString() + "/datafile.txt";
        private val BUFFER_SIZE = 8192;
        private val ENCODING = "US-ASCII";
        private val LINES_IN_BLOCK = 100000;
        private var mLogReader: Long = -1;
        private val mLogWriter = ResultLogWriter();
    }

    interface AsyncResponse {
        fun onFinished(result : String);
        fun onMatchFound(line: String);
    }

    private var mAsyncResponse : AsyncResponse? = null;

    constructor(asyncResponse: AsyncResponse) : super(){
        mAsyncResponse = asyncResponse;
    }

    private fun downloadFile(urlAddress: String): String {
        var count = 0;
        var status: String = SUCCESS;
        var input: InputStream? = null;
        var output: OutputStream? = null;
        try {
            var url = URL(urlAddress);
            var connection: URLConnection = url.openConnection();
            connection.connect();
            input = BufferedInputStream(url.openStream(), BUFFER_SIZE);
            output = FileOutputStream(DATA_FILE_NAME);

            var data = ByteArray(BUFFER_SIZE);
            while ({count = input.read(data); count}() != -1) {
                output.write(data, 0, count);
            }
            output.flush();
        } catch (e : IOException) {
            if (!Constants.PRODUCTION) {
                Log.e(TAG, "Error: " + e.toString());
            }
            status = "Error during downloading";
        }
        finally{
            try {
                if(output != null) {
                    output.close();
                }
                if (input != null) {
                    input.close();
                }
            }catch (e: IOException) {
                if (!Constants.PRODUCTION) {
                    Log.e(TAG, "Error: " + e.toString());
                }
                status = "Error during downloading";
            }
        }
        return status;
    }

    private fun parseFile(): String {
        var status = SUCCESS;
        var inputStream: FileInputStream? = null;
        var sc: Scanner? = null;
        try {
            inputStream = FileInputStream(DATA_FILE_NAME);
            sc = Scanner(inputStream);
            var counter = 0;
            val sb = StringBuffer();
            while (sc.hasNextLine()) {
                var line: String = sc.nextLine();
                sb.append(line + '\n');
                ++counter;
                if (counter == LINES_IN_BLOCK) {
                    var bytes: ByteArray = sb.toString().toByteArray(Charset.forName(ENCODING));
                    addSourceBlock(mLogReader, bytes, bytes.size);
                    sb.setLength(0);
                    counter = 0;
                }
            }
            if (counter > 0) {
                var bytes: ByteArray = sb.toString().toByteArray(Charset.forName(ENCODING));
                addSourceBlock(mLogReader, bytes, bytes.size);
            }
            if (sc.ioException() != null) {
                status = "Error parsing file";
            }
        } catch (e: IOException) {
            Log.e(TAG, "Error: " + e.toString());
            status = "Error parsing file";
        } finally {
            if (inputStream != null) {
                try {
                    inputStream.close();
                } catch (e: IOException) {
                    Log.e(TAG, "Error: " + e.toString());
                    status = "Error parsing file";
                }
            }
            if (sc != null) {
                sc.close();
            }
        }
        return status;
    }

    private fun convertToASCIIString(value: String): ByteArray {
        var sb = StringBuffer();
        sb.append(value);
        sb.append(java.lang.Character.MIN_VALUE);
        return sb.toString().toByteArray(Charset.forName(ENCODING));
    }

    override fun doInBackground(vararg args : String): String {
        var status: String;
        status = downloadFile(args[0]);
        if (!status.equals(SUCCESS)) {
            return status;
        }
        mLogReader = init(this);
        setFilter(mLogReader, convertToASCIIString(args[1]));
        mLogWriter.init();
        status = parseFile();
        deinit(mLogReader);
        return status;
    }

    protected override fun onPostExecute(result: String) {
        mLogWriter.deinit();
        mAsyncResponse?.onFinished(result);
    }

    public fun onMatchFound(line: String) {
        mLogWriter.write(line);
        mAsyncResponse?.onMatchFound(line);
    }

    private external fun init(ref: AnalyzerAsyncTask): Long

    private external fun deinit(logReader: Long);

    private external fun setFilter(logReader: Long, filter: ByteArray);

    private external fun addSourceBlock(logReader: Long, block: ByteArray, block_size: Int);
}
