package com.utkin.analyzerapp

import android.app.Fragment;
import android.content.ClipData;
import android.content.ClipboardManager;
import android.content.Context;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;

class AnalyzerListFragment : Fragment(), AnalyzerAsyncTask.AsyncResponse {

    private val STATUS = "STATUS";
    private val CLIPBOARD_LABEL = "CLIPBOARD_LABEL";

    private var mListAdapter: AnalyzerListAdapter? = null;
    private var mUrl: EditText? = null;
    private var mFilter: EditText? = null;
    private var mDownloadButton: Button? = null;
    private var mStatus: TextView? = null;
    private var mListView: ListView? = null;
    private var mData = mutableListOf<AnalyzerListItem>();
    private var mTask: AnalyzerAsyncTask? = null;
    private var mClipboard = mutableListOf<String>();

    public override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState);
        mListAdapter = AnalyzerListAdapter(getActivity());
        setRetainInstance(true);
    }

    private fun updateClipboard() {
        var sb: StringBuffer = StringBuffer();
        for (str in mClipboard) {
            sb.append(str + "\n");
        }
        var clipboard: ClipboardManager =
            getActivity().getSystemService(Context.CLIPBOARD_SERVICE) as ClipboardManager;
        var clip: ClipData = ClipData.newPlainText(CLIPBOARD_LABEL, sb.toString());
        clipboard.setPrimaryClip(clip);
    }

    private fun updateList() {
        mListAdapter?.clear();
        mListAdapter?.addAll(mData);
        mListAdapter?.notifyDataSetChanged();
    }


    public override fun onCreateView(
        inflater: LayoutInflater?,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        var view = inflater?.inflate(R.layout.listview, null);
        mDownloadButton = view?.findViewById(R.id.download_btn);
        mUrl = view?.findViewById(R.id.url);
        mFilter = view?.findViewById(R.id.filter);
        mListView = view?.findViewById(R.id.list);
        mListView?.setAdapter(mListAdapter);
        mListView?.setOnItemClickListener { parent, view, position, id ->
            var text = (view.getTag(R.id.title) as TextView).getText().toString();
            if (view.isActivated()) {
                mClipboard.add(text);
            } else {
                mClipboard.remove(text);
            }
            updateClipboard();
        };

        mStatus = view?.findViewById(R.id.status);

        if (savedInstanceState != null) {
            mStatus?.setText(savedInstanceState.getString(STATUS));
        }

        mDownloadButton?.setOnClickListener { v ->
            if (mTask == null) {
                mData.clear();
            }
            updateList();
            mStatus?.setText(AnalyzerAsyncTask.PROCESSING);
            mTask = AnalyzerAsyncTask(this@AnalyzerListFragment);
            mTask?.execute(mUrl?.getText().toString(), mFilter?.getText().toString());
        };
        return view;
    }

    public override fun onFinished(result: String) {
        mStatus?.setText(result);
        mTask = null;
    }

    public override fun onMatchFound(line: String) {
        getActivity().runOnUiThread {
            mData.add(AnalyzerListItem(line));
            updateList();
        };
    }

    public override fun onSaveInstanceState(bundle: Bundle) {
        super.onSaveInstanceState(bundle);
        bundle.putString(STATUS, mStatus?.getText().toString());
    }
}
