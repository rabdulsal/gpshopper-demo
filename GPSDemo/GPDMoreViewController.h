//
//  GPDMoreViewController.h
//  GPSDemo
//
//  Created by James Lee on 10/10/14.
//  Copyright (c) 2014 James Lee. All rights reserved.
//

#import "GPDViewController.h"

@interface GPDMoreViewController : GPDViewController <UITableViewDataSource, UITableViewDelegate>

@property (copy, nonatomic) NSArray *viewControllers;
@end
