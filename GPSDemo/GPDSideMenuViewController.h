//
//  GPDSideMenuViewController.h
//  GPSDemo
//
//  Created by James Lee on 5/10/14.
//  Copyright (c) 2014 James Lee. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "TWTSideMenuViewController.h"

@interface GPDSideMenuViewController : UIViewController <UITableViewDataSource, UITableViewDelegate, TWTSideMenuViewControllerDelegate>

@property (strong, nonatomic) IBOutlet UITableView *tableView;
@property (strong, nonatomic) NSArray *viewControllers;
@property (strong, nonatomic) IBOutlet UISearchBar *searchBar;

@property (strong, nonatomic, readonly) UINavigationController *activeNavigationStack;

- (void)goToSearchForQuery:(NSString *)query;
- (void)setActiveViewController:(UIViewController *)vc;
@end
