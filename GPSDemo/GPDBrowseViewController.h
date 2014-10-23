//
//  GPDBrowseViewController.h
//  GPSDemo
//
//  Created by James Lee on 5/10/14.
//  Copyright (c) 2014 James Lee. All rights reserved.
//

#import "GPDViewController.h"

@interface GPDBrowseViewController : GPDViewController <UITableViewDataSource, UITableViewDelegate, UISearchBarDelegate>

@property (strong, nonatomic) SCBrowseNode *node;

@property (strong, nonatomic) IBOutlet UITableView *tableView;

@end
