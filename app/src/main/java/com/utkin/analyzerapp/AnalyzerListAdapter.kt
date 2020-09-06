package com.utkin.analyzerapp

import android.app.Activity
import android.content.Context
import android.view.View
import android.view.ViewGroup
import android.widget.ArrayAdapter
import android.widget.TextView

class AnalyzerListAdapter: ArrayAdapter<AnalyzerListItem> {
    constructor(context: Context): super(context, 0);

    override fun getView(position: Int, view: View?, parent: ViewGroup): View {
        var convertView: View? = view;
        if(convertView == null) {
            var hostActivity: Activity  =  this.getContext() as Activity;
            convertView = hostActivity.getLayoutInflater().inflate(R.layout.listitem, null);
            convertView.setTag(R.id.title, convertView.findViewById(R.id.title));
        }
        ((convertView?.getTag(R.id.title))as TextView).setText(getItem(position)?.getTitle());
        return convertView;
    }
}
